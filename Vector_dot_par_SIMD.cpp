//
// Created by dinhd on 12/15/2025.
//

#include "Vector_dot_par_SIMD.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <omp.h>
#include <stdexcept>

void vector_dot_par_simdncache(
    int num_of_threads,
    const std::vector<double>& v1,
    const std::vector<double>& v2,
    double& time_taken
) {
    if (v1.size() != v2.size()) {
        throw std::runtime_error("Vector sizes do not match");
    }

    const std::size_t N = v1.size();
    const double* A = v1.data();
    const double* B = v2.data();

    omp_set_num_threads(num_of_threads);

    double sum = 0.0;

    // Block size: ~32KB (L1 cache friendly)
    constexpr std::size_t BLOCK = 4096; // 4096 * 8 bytes ≈ 32KB

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for schedule(static) reduction(+:sum)
    for (std::size_t ii = 0; ii < N; ii += BLOCK) {
        std::size_t end = (ii + BLOCK < N) ? ii + BLOCK : N;

#pragma omp simd
        for (std::size_t i = ii; i < end; ++i) {
            sum += A[i] * B[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    time_taken =
        std::chrono::duration<double>(end - start).count();

    std::cout << "Sum of vector dot product is (OpenMP + SIMD + L1 cache): " << sum << std::endl;
    std::cout << "Time taken is: " << time_taken*1000 << "ms"<< std::endl;
    std::cout << "Number of threads is " << num_of_threads <<""<< std::endl;

}


