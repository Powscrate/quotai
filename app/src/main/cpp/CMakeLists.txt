cmake_minimum_required(VERSION 3.22.1)

project("quotai-jni")

# Optimisations pour Android (vitesse de calcul du modèle)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fPIC -std=c++17")

# Activation des instructions NEON (essentiel pour la vitesse de l'IA sur ARM)
if(ANDROID_ABI STREQUAL "arm64-v8a")
    add_definitions(-DGGML_USE_NEON)
endif()

# Définition de la bibliothèque JNI
# On liste ici quotai-jni.cpp ET les fichiers sources de llama.cpp que tu vas ajouter
add_library(${PROJECT_NAME} SHARED
    quotai-jni.cpp
    llama.cpp
    llama-model-loader.cpp
    llama-model-saver.cpp
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
    ggml-alloc.c
    ggml-backend.cpp
    # ggml-backend-cuda.cpp
    # ggml-backend-metal.cpp
    llama-version.cpp
    ggml-quants.c
    gguf.cpp
    ggml-cpu.cpp
    ggml-opt.cpp
    ggml-threading.cpp
    binary-ops.cpp
    repack.cpp
    common.cpp
    ops.cpp
    vec.cpp
    fit.cpp
    log.cpp
    sampling.cpp
    reasoning-budget.cpp
    speculative.cpp
    ngram-cache.cpp
    ngram-map.cpp
    ngram-mod.cpp
    traits.cpp
    unary-ops.cpp
    hbm.cpp
)

# Ajout des fichiers RISC-V uniquement si l'architecture correspond
if(ANDROID_ABI MATCHES "riscv64")
    target_sources(${PROJECT_NAME} PRIVATE
        ime.cpp
        ime_env.cpp
        spine_mem_pool.cpp
    )
endif()

# Inclusion du dossier courant pour trouver les fichiers .h pour le projet
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Liens vers les bibliothèques Android nécessaires
target_link_libraries(${PROJECT_NAME}
    android
    log
    jnigraphics
)

# Configuration spécifique pour éviter les erreurs de symboles manquants
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON)