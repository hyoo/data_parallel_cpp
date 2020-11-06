#include <CL/sycl.hpp>
#include <array>

namespace sycl = cl::sycl;
constexpr int N = 42;

int main() {
    sycl::queue Q;

    std::array<int, N> host_array;
    int *device_array = sycl::malloc_device<int>(N, Q);

    for (int i = 0; i < N; i++)
        host_array[i] = N;
    
    Q.submit([&](sycl::handler &h) {
        h.memcpy(device_array, &host_array[0], N * sizeof(int));
    });
    Q.wait();

    Q.submit([&](sycl::handler &h) {
        h.parallel_for(N, [=](sycl::id<1> i) {
            device_array[i]++;
        });
    });
    Q.wait();

    Q.submit([&](sycl::handler &h) {
        h.memcpy(&host_array[0], device_array, N * sizeof(int));
    });
    Q.wait();

    for (int i = 0; i < N; i++)
        std::cout << "host_array[" << i << "] = " << host_array[i] << "\n";

    free(device_array, Q);
    return 0;
}