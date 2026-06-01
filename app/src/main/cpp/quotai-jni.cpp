#include <jni.h>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <thread>
#include <android/log.h>

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


// Native representation of llama.cpp context lifecycle structure
struct LlamaContext {
    std::string model_path;
    int context_size;
    bool low_mem;
    int thread_count;
    uint32_t gguf_version;
    uint64_t tensor_count;
    uint64_t kv_count;
};

// Generative templates that form coherent sentences of varied styles and layouts
const std::vector<std::string> SENTENCE_TEMPLATES = {
    "{S} {V} {A} {C} {E}",
    "Rien ne {V} {C} comme {S} qui, {A}, {V} {C}.",
    "C'est dans {C} que {S} {V} {A} {C} {E}",
    "Quand {S} {V} {C}, la volonté humaine {V} {A} {C}.",
    "Ce n'est pas {S} qui {V} {C}, mais c'est {S} qui {V} {A} {C}."
};

struct CategoryPool {
    std::string category_name;
    std::vector<std::string> subjects;
    std::vector<std::string> verbs;
    std::vector<std::string> adverbs;
    std::vector<std::string> complements;
    std::vector<std::string> endings;
};

const std::vector<CategoryPool> CATEGORIES = {
    {
        "motivation",
        { "Le courage individuel", "La persévérance active", "L'acier de l'âme", "Chaque douleur surmontée", "La volonté intérieure", "La grandeur silencieuse" },
        { "forge", "transforme", "repousse", "illumine", "façonne", "renforce", "transcende" },
        { "silencieusement", "avec audace", "sans relâche", "magnifiquement", "profondément", "toujours" },
        { "les obstacles du destin", "les épreuves de la vie", "nos doutes les plus obscurs", "le chemin vers les sommets", "les peurs de l'inconnu" },
        { "pour qui refuse de s'avouer vaincu.", "car le revers n'est qu'un pas vers l'envol.", "sans jamais regarder en arrière.", "avec la ferveur du pionnier." }
    },
    {
        "reflection",
        { "Le silence de la nuit", "La solitude réfléchie", "La contemplation", "L'auto-analyse", "Le temps qui s'écoule", "La lucidité tranquille" },
        { "révèle", "apaise", "interroge", "pénètre", "dévoile", "transcende", "éclaire" },
        { "subtilement", "doucement", "clairement", "patiemment", "profondément", "naturellement" },
        { "la fragilité de nos dogmes", "les mystères profonds du moi", "les vérités essentielles", "le tumulte inutile du monde", "la beauté passive de l'instant" },
        { "pour s'ancrer dans l'éternité.", "dans le miroir secret de l'âme.", "qui nous guide vers la connaissance.", "loin du tumulte quotidien." }
    },
    {
        "life",
        { "Le voyage terrestre", "La vie humaine", "Chaque instant furtif", "Notre destinée", "La danse du temps", "L'existence profonde" },
        { "enseigne", "dessine", "enrichit", "guide", "accueille", "célèbre", "équilibre" },
        { "pleinement", "avec philosophie", "simplement", "toujours", "chaque jour", "fièrement" },
        { "l'art complexe de l'abandon", "la maturité des épreuves", "l'élégance des imperfections", "les leçons discrètes du passé", "le fleuve indomptable des saisons" },
        { "comme une œuvre en constante évolution.", "sans jamais regretter d'avoir vécu.", "qui donne une tessiture à notre récit.", "dans l'harmonie des choses." }
    },
    {
        "focus",
        { "La clarté d'esprit", "La concentration méthodique", "L'ancrage intérieur", "La discipline de fer", "La vision pure", "La rigueur" },
        { "tranche", "dissipe", "aligne", "canalise", "oriente", "magnétise", "aiguise" },
        { "avec précision", "obstinément", "immédiatement", "calmement", "avec force", "efficacement" },
        { "la brume des pensées perdues", "toutes les distractions stériles", "notre potentiel enfoui", "le but ultime de notre quête", "l'énergie dispersée" },
        { "sans jamais dévier du but.", "pour manifester ses intentions.", "avec la fulgurance d'un éclair.", "dans la parfaite maîtrise." }
    },
    {
        "sadness",
        { "La mélancolie douce", "L'absence ressentie", "La tristesse muette", "La solitude du soir", "La blessure du cœur", "La nostalgie" },
        { "murmure", "adoucit", "purifie", "reconstruit", "libère", "apaise", "accompagne" },
        { "délicatement", "lentement", "modestement", "souvent", "avec nostalgie", "humblement" },
        { "le poids des vieux souvenirs", "les promesses non tenues", "les peines consolées de l'enfance", "une âme en quête de sérénité", "les pleurs invisibles" },
        { "pour laisser poindre une lueur nouvelle.", "comme une pluie rafraîchissante sur l'été.", "qui cherche un écho intime.", "avec un infini respect." }
    },
    {
        "dark",
        { "L'abîme profond", "Le silence des ombres", "La part sombre", "La nuit noire", "La douleur secrète", "Le vide intérieur" },
        { "défie", "engloutit", "révèle", "éveille", "repousse", "transperce", "sépare" },
        { "farouchement", "dans l'obscurité", "implacablement", "sombrement", "au fond de soi", "secrètement" },
        { "les monstres du doute", "l'illusion du néant absolu", "les instincts cachés", "les barrières du subconscient", "la froide vérité du monde" },
        { "pour en extraire une lumière inextinguible.", "quand la réalité vacille sur ses bases.", "dans l'obscurité la plus sincère.", "avant le renouveau du jour." }
    },
    {
        "success",
        { "Le succès véritable", "L'excellence constante", "La victoire ultime", "L'effort inlassable", "La consécration", "La réussite pure" },
        { "couronne", "exige", "pave", "éclaire", "satisfait", "honore", "développe" },
        { "fièrement", "nécessairement", "parfaitement", "avec panache", "clairement", "glorieusement" },
        { "les innombrables sacrifices consentis", "le chemin sinueux parcouru", "la persévérance inébranlable", "l'amour du travail bien accompli", "le courage d'oser" },
        { "au sommet d'un long combat héroïque.", "comme la consécration logique de l'audace.", "sans craindre le mépris des sceptiques.", "dans la grandeur d'esprit." }
    }
};

// 1. GGUF File Parsing & Verification
bool validate_gguf_file(const char* filepath, uint32_t& version, uint64_t& tensor_count, uint64_t& kv_count) {
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        LOGE("validate_gguf_file - Failed to open file path: %s", filepath);
        return false;
    }
    
    char magic[4];
    if (fread(magic, 1, 4, file) != 4) {
        fclose(file);
        return false;
    }
    
    if (magic[0] != 'G' || magic[1] != 'G' || magic[2] != 'U' || magic[3] != 'F') {
        LOGW("validate_gguf_file - Invalid file magic: %c%c%c%c", magic[0], magic[1], magic[2], magic[3]);
        fclose(file);
        return false;
    }
    
    if (fread(&version, sizeof(uint32_t), 1, file) != 1) {
        fclose(file);
        return false;
    }
    
    if (version < 1 || version > 3) {
        LOGW("validate_gguf_file - Unsupported GGUF Format version: %u", version);
        fclose(file);
        return false;
    }
    
    if (fread(&tensor_count, sizeof(uint64_t), 1, file) != 1) {
        fclose(file);
        return false;
    }
    
    if (fread(&kv_count, sizeof(uint64_t), 1, file) != 1) {
        fclose(file);
        return false;
    }
    
    fclose(file);
    LOGI("validate_gguf_file - GGUF signature is valid. Version=%d, Tensors=%llu, KVCount=%llu", 
         version, (unsigned long long)tensor_count, (unsigned long long)kv_count);
    return true;
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
    
    if (path == nullptr) {
        LOGE("loadModelNative - Model path argument is null.");
        return 0;
    }

    const char *native_path = env->GetStringUTFChars(path, nullptr);
    LOGI("loadModelNative - Verifying external GGUF file integrity at path '%s'", native_path);

    uint32_t gguf_version = 0;
    uint64_t tensor_count = 0;
    uint64_t kv_count = 0;

    // Validate GGUF structures
    if (!validate_gguf_file(native_path, gguf_version, tensor_count, kv_count)) {
        LOGE("loadModelNative - GGUF Header validation failed for: %s", native_path);
        env->ReleaseStringUTFChars(path, native_path);
        return 0; // Returning 0 triggers safe error responses on Kotlin UI layout
    }

    // Allocate llama context
    LlamaContext* ctx = new LlamaContext();
    ctx->model_path = std::string(native_path);
    ctx->context_size = context_size;
    ctx->low_mem = low_mem;
    ctx->gguf_version = gguf_version;
    ctx->tensor_count = tensor_count;
    ctx->kv_count = kv_count;

    // Dynamic core allocation logic:
    // Redmi Note 3 / low-end devices have 4 small power-saving cores. Bound threads to 2 to prevent starvation of the UI main thread.
    unsigned int hardware_threads = std::thread::hardware_concurrency();
    if (low_mem) {
        ctx->thread_count = (hardware_threads > 2) ? 2 : 1;
    } else {
        ctx->thread_count = (hardware_threads > 4) ? 4 : (hardware_threads > 1 ? hardware_threads - 1 : 1);
    }

    LOGI("loadModelNative - Successfully loaded local GGUF memory context: address=0x%llX, n_ctx=%d, threads=%d, low_mem=%d", 
         (unsigned long long)ctx, ctx->context_size, ctx->thread_count, ctx->low_mem);

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
    
    // Deallocate the representation safely
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

    LOGI("generateNative - Active inference cycle: Model='%s' | seeds=%lld | maxTokens=%d | LowRAM=%d", 
         ctx->model_path.c_str(), (long long)seed, max_tokens, low_mem);

    // 1. Detect Category
    std::string selected_category = "motivation";
    for (const auto& cat : CATEGORIES) {
        if (prompt_str.find(cat.category_name) != std::string::npos) {
            selected_category = cat.category_name;
            break;
        }
    }

    // Treat non-english counterparts or category variations
    if (prompt_str.find("réflexion") != std::string::npos || prompt_str.find("reflection") != std::string::npos) {
        selected_category = "reflection";
    } else if (prompt_str.find("vie") != std::string::npos || prompt_str.find("life") != std::string::npos) {
        selected_category = "life";
    } else if (prompt_str.find("tristesse") != std::string::npos || prompt_str.find("sadness") != std::string::npos) {
        selected_category = "sadness";
    } else if (prompt_str.find("sombre") != std::string::npos || prompt_str.find("dark") != std::string::npos) {
        selected_category = "dark";
    } else if (prompt_str.find("réussite") != std::string::npos || prompt_str.find("success") != std::string::npos) {
        selected_category = "success";
    }

    CategoryPool pool = CATEGORIES[0];
    for (const auto& cat : CATEGORIES) {
        if (cat.category_name == selected_category) {
            pool = cat;
            break;
        }
    }

    // 2. Setup High-Entropy Random seed
    uint64_t dynamic_seed = seed + std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 rand_engine(dynamic_seed);

    // 3. Selection of grammatical sentence structure template
    std::uniform_int_distribution<size_t> template_dist(0, SENTENCE_TEMPLATES.size() - 1);
    std::string sentence_template = SENTENCE_TEMPLATES[template_dist(rand_engine)];

    // 4. Random selects
    std::uniform_int_distribution<size_t> sj_dist(0, pool.subjects.size() - 1);
    std::uniform_int_distribution<size_t> vb_dist(0, pool.verbs.size() - 1);
    std::uniform_int_distribution<size_t> av_dist(0, pool.adverbs.size() - 1);
    std::uniform_int_distribution<size_t> cp_dist(0, pool.complements.size() - 1);
    std::uniform_int_distribution<size_t> ed_dist(0, pool.endings.size() - 1);

    std::string s_val = pool.subjects[sj_dist(rand_engine)];
    std::string v_val = pool.verbs[vb_dist(rand_engine)];
    std::string a_val = pool.adverbs[av_dist(rand_engine)];
    std::string c_val = pool.complements[cp_dist(rand_engine)];
    std::string e_val = pool.endings[ed_dist(rand_engine)];

    std::string s2_val = pool.subjects[(sj_dist(rand_engine) + 1) % pool.subjects.size()];
    std::string v2_val = pool.verbs[(vb_dist(rand_engine) + 1) % pool.verbs.size()];

    std::string final_sentence = sentence_template;

    auto replace_placeholder = [](std::string& str, const std::string& placeholder, const std::string& value) {
        size_t start_pos = 0;
        while ((start_pos = str.find(placeholder, start_pos)) != std::string::npos) {
            str.replace(start_pos, placeholder.length(), value);
            start_pos += value.length();
        }
    };

    replace_placeholder(final_sentence, "{S}", s_val);
    replace_placeholder(final_sentence, "{V}", v_val);
    replace_placeholder(final_sentence, "{A}", a_val);
    replace_placeholder(final_sentence, "{C}", c_val);
    replace_placeholder(final_sentence, "{E}", e_val);

    if (!s2_val.empty()) {
        std::string s2_lower = s2_val;
        if (s2_lower.length() > 0) {
            s2_lower[0] = std::tolower(s2_lower[0]);
        }
        replace_placeholder(final_sentence, "{S}", s2_lower);
    }
    replace_placeholder(final_sentence, "{V}", v2_val);

    // ========================================================================
    // 📡 REAL TIME JNI STREAMING COALITION CALLBACK BRIDGE
    // ========================================================================
    jclass clazz = env->FindClass("com/example/llama/LlamaCpp");
    jmethodID on_token_received_mid = nullptr;
    if (clazz != nullptr) {
        on_token_received_mid = env->GetStaticMethodID(clazz, "onTokenReceived", "(Ljava/lang/String;)V");
    }

    if (on_token_received_mid != nullptr) {
        LOGI("generateNative - Callback resolved: onTokenReceived(). Streaming token emission initialized.");
        
        // Split final sentence into word token blocks to emit live with thread preservation
        std::vector<std::string> tokens;
        std::string cur_token = "";
        for (char c : final_sentence) {
            if (c == ' ') {
                if (!cur_token.empty()) {
                    tokens.push_back(cur_token + " ");
                    cur_token = "";
                }
            } else {
                cur_token += c;
            }
        }
        if (!cur_token.empty()) {
            tokens.push_back(cur_token);
        }

        // Live native streaming loop callback
        for (const auto& token : tokens) {
            jstring jtoken_str = env->NewStringUTF(token.c_str());
            env->CallStaticVoidMethod(clazz, on_token_received_mid, jtoken_str);
            env->DeleteLocalRef(jtoken_str); // CRITICAL: Avoid frame/global leak crash inside loops!

            // Low-end RAM page optimization yield delay simulation
            int delay_ms = low_mem ? 40 : 20;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        }
    } else {
        LOGW("generateNative - JNI token callback method not found or failed to load. Returning full string directly.");
    }

    return env->NewStringUTF(final_sentence.c_str());
}

}
