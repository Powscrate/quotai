#include "llama.h"

// These functions provide build information
int llama_build_number(void) {
    return 1;  // Version number
}

const char * llama_commit(void) {
    return "custom-build";
}

const char * llama_compiler(void) {
#if defined(__clang__)
    return "clang";
#elif defined(_MSC_VER)
    return "msvc";
#elif defined(__GNUC__)
    return "gcc";
#else
    return "unknown";
#endif
}

const char * llama_build_target(void) {
    return "arm64-v8a";  // Or detect dynamically if needed
}