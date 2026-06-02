#include <jni.h>
#include <string>
#include <vector>
#include <thread>
#include <android/log.h>

#include "llama.h"

#define LOG_TAG "QuotAI_JNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

struct LlamaContext {
    llama_model* model = nullptr;
    llama_context* ctx = nullptr;

    ~LlamaContext() {
        if (ctx) llama_free(ctx);
        if (model) llama_model_free(model);
    }
};

extern "C" {

JNIEXPORT jlong JNICALL
Java_com_example_llama_LlamaCpp_loadModelNative(
        JNIEnv *env,
        jobject,
        jstring path,
        jint context_size,
        jboolean low_mem) {

    llama_backend_init();

    const char *native_path = env->GetStringUTFChars(path, nullptr);

    llama_model_params mparams = llama_model_default_params();
    mparams.use_mmap = true;

    llama_model *model = llama_model_load_from_file(native_path, mparams);
    if (!model) {
        env->ReleaseStringUTFChars(path, native_path);
        return 0;
    }

    llama_context_params cparams = llama_context_default_params();
    cparams.n_ctx = context_size;
    cparams.n_threads = std::max(1, (int)std::thread::hardware_concurrency() / (low_mem ? 2 : 1));

    llama_context *ctx = llama_init_from_model(model, cparams);
    if (!ctx) {
        llama_model_free(model);
        env->ReleaseStringUTFChars(path, native_path);
        return 0;
    }

    auto *wrapper = new LlamaContext();
    wrapper->model = model;
    wrapper->ctx = ctx;

    env->ReleaseStringUTFChars(path, native_path);
    return (jlong)wrapper;
}

JNIEXPORT void JNICALL
Java_com_example_llama_LlamaCpp_unloadModelNative(
        JNIEnv *,
        jobject,
        jlong ptr) {

    delete (LlamaContext*)ptr;
}

JNIEXPORT jstring JNICALL
Java_com_example_llama_LlamaCpp_generateNative(
        JNIEnv *env,
        jobject,
        jlong ptr,
        jlong,
        jstring prompt,
        jint max_tokens,
        jboolean) {

    auto *lc = (LlamaContext*)ptr;

    const char *c_prompt = env->GetStringUTFChars(prompt, nullptr);

    const std::string prompt_str = c_prompt;
    env->ReleaseStringUTFChars(prompt, c_prompt);

    llama_token tokens[2048];

    int n_tokens = llama_tokenize(
        lc->model,
        prompt_str.c_str(),
        prompt_str.size(),
        tokens,
        2048,
        true,
        true
    );

    llama_batch batch = llama_batch_init(2048, 0, 1);

    for (int i = 0; i < n_tokens; i++) {
        llama_batch_add(batch, tokens[i], i, {0}, false);
    }

    llama_batch_add(batch, 0, n_tokens, {0}, true);

    std::string result;

    for (int i = 0; i < max_tokens; i++) {

        if (llama_decode(lc->ctx, batch) != 0)
            break;

        llama_token new_token = llama_sample_token_greedy(lc->ctx, lc->model);

        if (llama_vocab_is_eog(llama_model_get_vocab(lc->model), new_token))
            break;

        char buf[256];
        int n = llama_token_to_piece(
            lc->model,
            new_token,
            buf,
            sizeof(buf),
            0,
            true
        );

        if (n > 0) {
            result.append(buf, n);
        }

        batch = llama_batch_init(1, 0, 1);
        llama_batch_add(batch, new_token, i, {0}, true);
    }

    return env->NewStringUTF(result.c_str());
}

}