#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Vector_dot_seq.h"
#include "Vector_dot_par.h"
#include "Vector_dot_par_SIMD.h"

int main() {
    omp_set_num_threads(16);

    int num_of_threads = 16;
    const long N_size_of_data = 1000;

    // Cấp phát bộ nhớ
    std::vector<double> a(N_size_of_data);
    std::vector<double> b(N_size_of_data);

    // Khởi tạo vector ngẫu nhiên
    // (Lưu ý: Đoạn khởi tạo này cũng có thể song song hóa, nhưng ta tập trung vào phần tính tích)
    srand(time(NULL));
    #pragma omp parallel for
    for (long i = 0; i < N_size_of_data; i++) {
        a[i] = (double)(rand()) / RAND_MAX;
        b[i] = (double)(rand()) / RAND_MAX;
    }
    #pragma omp barrier
    //Hoàn thành khởi tạo hệ số của hai vector!
    std::cout << std::endl;

    std::cout << "Vector size is:" << N_size_of_data <<"\n" << std::endl;
    std::cout << "Initial done! Start computing...\n" << std::endl;
    std::cout << "  =========================== \n" << std::endl;

    double execution_time = 0.0;
    vector_dot_product_seq(a, b, execution_time);

    double execution_time_omp = 0.0;
    vector_dot_par(num_of_threads, a, b, execution_time_omp);

    double execution_time_omp_SIMD_Cache = 0.0;
    vector_dot_par_simdncache(num_of_threads, a, b, execution_time_omp_SIMD_Cache);
    return 0;
}