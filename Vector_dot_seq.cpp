#include "Vector_dot_seq.h"
#include <chrono>
#include <iostream>

void vector_dot_product_seq(const std::vector<double>& v1, const std::vector<double>& v2, double& time_taken) {

    if (v1.size() != v2.size()) {
        std::cerr << "Loi: Kich thuoc hai vector khong bang nhau!" << std::endl;
        time_taken = 0.0;
        return;
    }

    double result = 0.0;
    size_t n = v1.size();

    // Bắt đầu đo thời gian
    auto start_time = std::chrono::high_resolution_clock::now();

    // Tính tích vô hướng
    for (size_t i = 0; i < n; ++i) {
        result += v1[i] * v2[i];
    }

    // Kết thúc đo thời gian
    auto end_time = std::chrono::high_resolution_clock::now();

    // Tính khoảng thời gian (ms)
    std::chrono::duration<double, std::milli> duration = end_time - start_time;
    time_taken = duration.count();

    std::cout << "Sum of vector dot product seq is: " << result << std::endl;
    std::cout<< "Time taken (Seq) is: " << time_taken << "ms"<<std::endl;
    std::cout <<"========================================================="<< std::endl;
}