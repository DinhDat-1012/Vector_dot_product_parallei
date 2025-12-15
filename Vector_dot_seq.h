#ifndef VECTOR_DOT_SEQ_H
#define VECTOR_DOT_SEQ_H

#include <vector>

// Hàm thực hiện tích vô hướng tuần tự
// Input: v1, v2 (hai vector), time_taken (biến tham chiếu để lưu thời gian thực thi)
// Output: Kết quả tích vô hướng (long long để tránh tràn số)
void vector_dot_product_seq(const std::vector<double>& v1, const std::vector<double>& v2, double& time_taken);

#endif // VECTOR_DOT_SEQ_H