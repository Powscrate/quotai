cmake_minimum_required(VERSION 3.22.1)

project(quotai)

set(CMAKE_CXX_STANDARD 17)

# 🔥 IMPORTANT: reduce APK size
set(LLAMA_BUILD_TESTS OFF CACHE BOOL "")
set(LLAMA_BUILD_EXAMPLES OFF CACHE BOOL "")
set(LLAMA_BUILD_SERVER OFF CACHE BOOL "")
set(LLAMA_BUILD_COMMON ON CACHE BOOL "")  # ADD THIS LINE

add_subdirectory(llama)

add_library(quotai-jni SHARED
    quotai-jni.cpp
)
target_include_directories(quotai-jni PRIVATE
    llama/include
    llama/common
)
target_link_libraries(quotai-jni
    llama
    llama-common              # ADD THIS LINE
    android
    log
)