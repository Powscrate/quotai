#pragma once

#define LLAMA_BUILD_NUMBER 1
#define LLAMA_COMMIT "manual"
#define LLAMA_COMPILER "NDK"
#define LLAMA_BUILD_TARGET "Android"

inline int llama_build_number(void) { return LLAMA_BUILD_NUMBER; }
inline const char * llama_commit(void) { return LLAMA_COMMIT; }
inline const char * llama_compiler(void) { return LLAMA_COMPILER; }
inline const char * llama_build_target(void) { return LLAMA_BUILD_TARGET; }