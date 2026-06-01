cmake_minimum_required(VERSION 3.18.1)
project(quotai-jni)

add_library(quotai-jni SHARED
            src/main/cpp/quotai-jni.cpp)

find_library(log-lib log)

target_link_libraries(quotai-jni
                       ${log-lib})
