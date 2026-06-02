cmake_minimum_required(VERSION 3.22.1)

project(quotai)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(llama)

add_library(quotai-jni SHARED
    quotai-jni.cpp
)

target_include_directories(quotai-jni PRIVATE
    llama/include
    llama/common
    llama/src
)

target_link_libraries(quotai-jni
    llama
    android
    log
)