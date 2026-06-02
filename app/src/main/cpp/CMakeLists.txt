cmake_minimum_required(VERSION 3.22.1)

project(quotai-jni)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fPIC")

add_library(quotai-jni SHARED
    quotai-jni.cpp

    llama.cpp

    llama-adapter.cpp
    llama-chat.cpp
    llama-model.cpp
    llama-context.cpp
    llama-cparams.cpp
    llama-impl.cpp
    llama-graph.cpp
    llama-io.cpp
    llama-memory.cpp
    llama-mmap.cpp
    llama-batch.cpp
    llama-kv-cache.cpp
    llama-hparams.cpp
    llama-arch.cpp
    llama-vocab.cpp
    llama-grammar.cpp
    llama-sampler.cpp

    unicode.cpp
    unicode-data.cpp

    ggml.c
    ggml-quants.c
    ggml-alloc.c

    ggml-backend.cpp
    ggml-backend-reg.cpp

    gguf.cpp

    ggml-cpu.cpp
    ggml-cpu.c
    ggml-opt.cpp
    ggml-threading.cpp

    binary-ops.cpp
    unary-ops.cpp
    repack.cpp
    ops.cpp
    vec.cpp
    common.cpp
    fit.cpp
    log.cpp
    sampling.cpp
    speculative.cpp
    reasoning-budget.cpp

    sgemm.cpp
)

find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(quotai-jni
    ${log-lib}
    ${android-lib}
)