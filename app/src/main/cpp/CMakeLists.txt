cmake_minimum_required(VERSION 3.22.1)

project(quotai)

set(CMAKE_CXX_STANDARD 17)

# 🔥 IMPORTANT: reduce APK size
set(LLAMA_BUILD_TESTS OFF CACHE BOOL "")
set(LLAMA_BUILD_EXAMPLES OFF CACHE BOOL "")
set(LLAMA_BUILD_SERVER OFF CACHE BOOL "")
set(LLAMA_BUILD_COMMON ON CACHE BOOL "")  # ADD THIS LINE

# Find or fetch nlohmann_json
find_package(nlohmann_json 3.2.0 QUIET)
if(NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found, fetching from GitHub...")
    include(FetchContent)
    FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
    )
    FetchContent_MakeAvailable(json)
endif()

# Link it to your target (e.g., llama-common)
target_link_libraries(llama-common PUBLIC nlohmann_json::nlohmann_json)
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