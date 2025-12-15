//
// Created by dinhd on 12/15/2025.
//
#include <omp.h>
#include "Vector_dot_par.h"
#include <ctime>
#include <chrono>
#include <iostream>

void vector_dot_par(int num_of_threads, const std::vector<double>& v1, const std::vector<double>& v2, double& time_taken) {
    // 1. Kiểm tra kích thước
    if (v1.size() != v2.size()) {
        std::cerr << "Loi: Kich thuoc vector khong khop!" << std::endl;
        time_taken = 0.0;
        return;
    }

    size_t n = v1.size();
    double result = 0.0;


    omp_set_num_threads(num_of_threads);
    auto start_time = std::chrono::high_resolution_clock::now();

    // Tính toán song song
    #pragma omp parallel for reduction(+:result)
    for (size_t i = 0; i < n; ++i) {
        result += v1[i] * v2[i];
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;
    time_taken = duration.count();

    // 6. In kết quả
    std::cout << " Sum of vector dot product is (OpenMP - " << num_of_threads << " threads): " << result << std::endl;
    std::cout <<"Time taken is:" << time_taken <<"ms"<< std::endl;
    std::cout <<"=================================================================================" << std::endl;
}