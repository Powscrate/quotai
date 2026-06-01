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
    ggml.c
    ggml-alloc.c
    ggml-backend.cpp
    ggml-quants.c
    gguf.cpp
    ggml-cpu.cpp
    ggml-opt.cpp
)

# Inclusion du dossier courant pour trouver les fichiers .h
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_SOURCE_DIR}/ggml
)


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