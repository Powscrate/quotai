#include <jni.h>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <thread>
#include <android/log.h>

#include "llama.h"

#define LOG_TAG "QuotAI_JNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

/*
 * ============================================================================
 * 🛠️ HOW TO COMPILE llama.cpp FOR ANDROID (PRODUCTION DOCUMENTATION)
 * ============================================================================
 * 
 * To build llama.cpp as a shared or static library for Android (ARM64 and ARMv7),
 * follow these professional deployment instructions using the Android NDK:
 * 
 * 1. PREREQUISITES:
 *    - Android SDK & NDK (Bundle 25.x or newer).
 *    - CMake 3.22.1+ and Ninja Build.
 * 
 * 2. STANDALONE COMPILATION VIA CMAKE:
 *    Run the following script from your llama.cpp project root to build shared binaries:
 * 
 *    ```bash
 *    export NDK=$ANDROID_HOME/ndk/25.1.8937393 # Set your local NDK path
 *    
 *    # For 64-bit ARM (arm64-v8a) - Most modern devices
 *    cmake -H. -Bbuild_arm64 \
 *      -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
 *      -DANDROID_ABI=arm64-v8a \
 *      -DANDROID_PLATFORM=android-21 \
 *      -DGGML_OPENMP=OFF \
 *      -DGGML_NEON=ON \
 *      -DBUILD_SHARED_LIBS=ON \
 *      -DCMAKE_BUILD_TYPE=Release
 *    cmake --build build_arm64 --config Release
 * 
 *    # For 32-bit ARM (armeabi-v7a) - Legacy devices (like Redmi Note 3)
 *    cmake -H. -Bbuild_armv7 \
 *      -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
 *      -DANDROID_ABI=armeabi-v7a \
 *      -DANDROID_PLATFORM=android-21 \
 *      -DGGML_OPENMP=OFF \
 *      -DGGML_NEON=ON \
 *      -DANDROID_ARM_NEON=ON \
 *      -DBUILD_SHARED_LIBS=ON \
 *      -DCMAKE_BUILD_TYPE=Release
 *    cmake --build build_armv7 --config Release
 *    ```
 * 
 * 3. COPY BINARIES TO ANDROID PROJECT:
 *    Place the compiled shared libraries (`libllama.so` & `libggml.so`) into:
 *    `app/src/main/jniLibs/arm64-v8a/` and `app/src/main/jniLibs/armeabi-v7a/`.
 * 
 * 4. KEY OPTIMIZATIONS FOR MOBILE DEVICES:
 *    - MMAP Loading (-DGGML_USE_MMAP=ON): Allows mapping the GGUF model directly into memory-mapped space,
 *      releasing system memory pressure and using the Linux page cache. Prevents Out-Of-Memory (OOM) crashes.
 *    - Thread Constraints: Restrict thread count dynamically based on the device's CPU architecture.
 *      Do not exceed active physical core counts (e.g., 2 cores max on low-end dual-cluster designs).
 *    - FP16 & quantization (Q4_K_M, Q8_0): Ensure your model GGUF matches lower precision scales to reduce
 *      the key-value (KV) cache RAM footprint.
 * ============================================================================
 */

// Structure native pour gérer le cycle de vie de llama.cpp
struct LlamaContext {
    std::string model_path;
    llama_model* model = nullptr;
    llama_context* ctx = nullptr;

    ~LlamaContext() {
        if (ctx) {
            llama_free(ctx);
            ctx = nullptr;
        }
        if (model) {
            llama_model_free(model);
            model = nullptr;
        }
    }
};

// Helper pour ajouter des tokens au batch
static void batch_add(struct llama_batch & batch, llama_token id, llama_pos pos, const std::vector<llama_seq_id> & seq_ids, bool logits) {
    batch.token[batch.n_tokens] = id;
    batch.pos[batch.n_tokens]   = pos;
    batch.n_seq_id[batch.n_tokens] = seq_ids.size();
    for (size_t i = 0; i < seq_ids.size(); ++i) {
        batch.seq_id[batch.n_tokens][i] = seq_ids[i];
    }
    batch.logits[batch.n_tokens] = logits;
    batch.n_tokens++;
}

extern "C" {

// EXPOSED JNI METHOD FOR MODEL LOADING
JNIEXPORT jlong JNICALL
Java_com_example_llama_LlamaCpp_loadModelNative(
        JNIEnv *env,
        jobject thiz,
        jstring path,
        jint context_size,
        jboolean low_mem) {

    static bool backend_initialized = false;
    if (!backend_initialized) {
        llama_backend_init();
        backend_initialized = true;
        LOGI("loadModelNative - llama.cpp backend initialisé.");
    }

    if (path == nullptr) {
        LOGE("loadModelNative - Model path argument is null.");
        return 0;
    }

    const char *native_path = env->GetStringUTFChars(path, nullptr);
    LOGI("loadModelNative - Chargement du modèle : %s", native_path);

    // 1. Paramètres du modèle
    auto model_params = llama_model_default_params();
    model_params.use_mmap = true; 

    // 2. Chargement du modèle
    llama_model * model = llama_model_load_from_file(native_path, model_params);
    if (!model) {
        LOGE("loadModelNative - Impossible de charger le modèle.");
        env->ReleaseStringUTFChars(path, native_path);
        return 0;
    }

    // 3. Paramètres du contexte
    auto ctx_params = llama_context_default_params();
    ctx_params.n_ctx = context_size;
    ctx_params.n_threads = std::thread::hardware_concurrency();
    if (low_mem) {
        ctx_params.n_threads = std::max(1, (int)ctx_params.n_threads / 2);
    }

    // 4. Création du contexte
    llama_context * ctx_llama = llama_init_from_model(model, ctx_params);
    if (!ctx_llama) {
        LOGE("loadModelNative - Impossible de créer le contexte.");
        llama_model_free(model);
        env->ReleaseStringUTFChars(path, native_path);
        return 0;
    }

    LlamaContext* ctx = new LlamaContext();
    ctx->model_path = std::string(native_path);
    ctx->model = model;
    ctx->ctx = ctx_llama;

    LOGI("loadModelNative - Succès : address=0x%llX", (unsigned long long)ctx);

    env->ReleaseStringUTFChars(path, native_path);
    return reinterpret_cast<jlong>(ctx);
}

// EXPOSED JNI METHOD FOR MODEL UNLOADING (CLEAN CYCLE)
JNIEXPORT void JNICALL
Java_com_example_llama_LlamaCpp_unloadModelNative(
        JNIEnv *env,
        jobject thiz,
        jlong ctx_address) {
    if (ctx_address == 0) {
        LOGW("unloadModelNative - Attempted to unload an empty model address.");
        return;
    }

    LlamaContext* ctx = reinterpret_cast<LlamaContext*>(ctx_address);
    LOGI("unloadModelNative - Unloading GGUF llama structures from native heap (address 0x%llX)", (unsigned long long)ctx);
    
    delete ctx;
    
    LOGI("unloadModelNative - Native heap released. Memory isolation successful.");
}

// EXPOSED JNI METHOD FOR STREAMING GENERATION (TOKEN BY TOKEN CALLBACK BRIDGE)
JNIEXPORT jstring JNICALL
Java_com_example_llama_LlamaCpp_generateNative(
        JNIEnv *env,
        jobject thiz,
        jlong ctx_address,
        jlong seed,
        jstring prompt,
        jint max_tokens,
        jboolean low_mem) {

    if (ctx_address == 0) {
        LOGE("generateNative - Native model address is null.");
        return env->NewStringUTF("");
    }

    if (prompt == nullptr) {
        return env->NewStringUTF("");
    }

    LlamaContext* ctx = reinterpret_cast<LlamaContext*>(ctx_address);

    const char *native_prompt = env->GetStringUTFChars(prompt, nullptr);
    std::string prompt_str(native_prompt);
    env->ReleaseStringUTFChars(prompt, native_prompt);

    // 1. Tokenisation
    auto vocab = llama_model_get_vocab(ctx->model);
    std::vector<llama_token> tokens_list(prompt_str.size() + 2);
    int n_tokens = llama_tokenize(vocab, prompt_str.c_str(), prompt_str.size(), 
                                 tokens_list.data(), tokens_list.size(), true, true);
    if (n_tokens < 0) return env->NewStringUTF("");
    tokens_list.resize(n_tokens);

    // 2. Initialisation du Batch
    llama_batch batch = llama_batch_init(std::max(n_tokens, max_tokens), 0, 1);
    for (size_t i = 0; i < tokens_list.size(); ++i) {
        batch_add(batch, tokens_list[i], i, {0}, i == tokens_list.size() - 1);
    }

    // 3. Setup Callback
    jclass clazz = env->FindClass("com/example/llama/LlamaCpp");
    jmethodID on_token_received_mid = clazz ? env->GetStaticMethodID(clazz, "onTokenReceived", "(Ljava/lang/String;)V") : nullptr;
    
    // Setup Sampler (Greedy)
    struct llama_sampler * smpl = llama_sampler_init_greedy();

    // 4. Boucle d'inférence
    std::string full_res = "";
    int n_cur = tokens_list.size();
    int n_decode = 0;

    while (n_decode < max_tokens && n_cur < llama_n_ctx(ctx->ctx)) {
        if (llama_decode(ctx->ctx, batch) != 0) break;
        
        batch.n_tokens = 0;

        // Sampling
        const llama_token new_id = llama_sampler_sample(smpl, ctx->ctx, -1);

        // Fin de génération ?
        if (llama_vocab_is_eog(vocab, new_id)) break;

        char buf[128];
        int n = llama_token_to_piece(vocab, new_id, buf, sizeof(buf), 0, true);
        if (n > 0) {
            std::string piece(buf, n);
            full_res += piece;
            if (on_token_received_mid) {
                jstring jpiece = env->NewStringUTF(piece.c_str());
                env->CallStaticVoidMethod(clazz, on_token_received_mid, jpiece);
                env->DeleteLocalRef(jpiece);
            }
        }

        batch_add(batch, new_id, n_cur, {0}, true);
        n_cur++; n_decode++;
    }

    llama_batch_free(batch);
    llama_sampler_free(smpl);
    return env->NewStringUTF(full_res.c_str());
}

}
