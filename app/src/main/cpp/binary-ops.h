#pragma once

#include "common.h"
#include "ggml-impl.h"
#include <type_traits>
#include <utility>
#include <algorithm>

// Table de conversion de types pour les opérations binaires
template <typename T>
struct type_conversion_table {
    static constexpr auto to_f32 = [](T val) -> float {
        if constexpr (std::is_same_v<T, float>) return val;
        else if constexpr (std::is_same_v<T, ggml_fp16_t>) return ggml_fp16_to_fp32(val);
        else if constexpr (std::is_same_v<T, ggml_bf16_t>) return ggml_bf16_to_fp32(val);
        else return (float)val;
    };
    
    static constexpr auto from_f32 = [](float val) -> T {
        if constexpr (std::is_same_v<T, float>) return val;
        else if constexpr (std::is_same_v<T, ggml_fp16_t>) return ggml_fp32_to_fp16(val);
        else if constexpr (std::is_same_v<T, ggml_bf16_t>) return ggml_fp32_to_bf16(val);
        else return (T)val;
    };
};

// Calcul de la plage de threads
inline std::pair<int64_t, int64_t> get_thread_range(const struct ggml_compute_params * params, const struct ggml_tensor * tensor) {
    int64_t total_rows = 1;
    for (int i = 1; i < GGML_MAX_DIMS; i++) {
        total_rows *= tensor->ne[i];
    }
    int64_t rows_per_thread = (total_rows + params->nth - 1) / params->nth;
    int64_t ir0 = params->ith * rows_per_thread;
    int64_t ir1 = std::min(ir0 + rows_per_thread, total_rows);
    return {ir0, ir1};
}

#ifdef __cplusplus
extern "C" {
#endif

void ggml_compute_forward_add_non_quantized(const struct ggml_compute_params * params, struct ggml_tensor * dst);
void ggml_compute_forward_sub(const struct ggml_compute_params * params, struct ggml_tensor * dst);
void ggml_compute_forward_mul(const struct ggml_compute_params * params, struct ggml_tensor * dst);
void ggml_compute_forward_div(const struct ggml_compute_params * params, struct ggml_tensor * dst);

#ifdef __cplusplus
}
#endif