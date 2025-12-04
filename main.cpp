#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>

int main() {
    omp_set_num_threads(16);
    // 1. Cấu hình kích thước vector (N nên lớn để thấy sự khác biệt về tốc độ)
    const long N = 1539607511; // 50 triệu phần tử

    std::cout << "Dang khoi tao du lieu cho " << N << " phan tu..." << std::endl;

    // Cấp phát bộ nhớ
    std::vector<double> a(N);
    std::vector<double> b(N);

    // Khởi tạo vector ngẫu nhiên
    // (Lưu ý: Đoạn khởi tạo này cũng có thể song song hóa, nhưng ta tập trung vào phần tính tích)
    srand(time(NULL));
    #pragma omp parallel for
    for (long i = 0; i < N; i++) {
        a[i] = (double)(rand()) / RAND_MAX;
        b[i] = (double)(rand()) / RAND_MAX;
    }
    #pragma omp barrier

    std::cout << std::endl;
    std::cout << "Khoi tao xong. Bat dau tinh toan...\n" << std::endl;

    // --- TÍNH TUẦN TỰ (SEQUENTIAL) ---
    double seq_result = 0.0;
    double start_time = omp_get_wtime(); // Lấy thời gian bắt đầu

    for (long i = 0; i < N; i++) {
        seq_result += a[i] * b[i];
    }

    double end_time = omp_get_wtime(); // Lấy thời gian kết thúc
    double seq_duration = end_time - start_time;

    std::cout << "1. Ket qua Tuan tu (Sequential): " << std::fixed << std::setprecision(2) << seq_result << std::endl;
    std::cout << "   Thoi gian chay: " << std::setprecision(5) << seq_duration << " giay" << std::endl;


    // --- TÍNH SONG SONG (OPENMP PARALLEL) ---
    double par_result = 0.0;
    start_time = omp_get_wtime();

    // Chỉ thị OpenMP:
    // parallel for: Chia vòng lặp cho các luồng (threads)
    // reduction(+:par_result): Mỗi luồng tính tổng riêng, sau đó cộng gộp vào par_result
    #pragma omp parallel for reduction(+:par_result)
    for (long i = 0; i < N; i++) {
        par_result += a[i] * b[i];
    }

    end_time = omp_get_wtime();
    double par_duration = end_time - start_time;

    std::cout << "\n2. Ket qua Song song (OpenMP):   " << std::fixed << std::setprecision(2) << par_result << std::endl;
    std::cout << "   Thoi gian chay: " << std::setprecision(5) << par_duration << " giay" << std::endl;

    // --- SO SÁNH ---
    std::cout << "\n---------------------------------" << std::endl;
    if (par_duration < seq_duration) {
        std::cout << "OpenMP nhanh hon gap: " << seq_duration / par_duration << " lan" << std::endl;
    } else {
        std::cout << "OpenMP cham hon hoac tuong duong (do overhead hoac du lieu qua it)." << std::endl;
    }

    // In số lượng threads đã dùng
    int num_threads = 1;
    #pragma omp parallel
    {
        #pragma omp single
        num_threads = omp_get_num_threads();
    }
    std::cout << "So luong threads da su dung: " << num_threads << std::endl;

    return 0;
}