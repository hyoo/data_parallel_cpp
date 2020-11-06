#include <CL/sycl.hpp>
#include <array>

namespace sycl = cl::sycl;
constexpr int N = 42;

int main() {
    sycl::queue Q;

    // int *host_array = sycl::malloc_host<int>(N, Q);
    int *shared_array = sycl::malloc_shared<int>(N, Q);

    for (int i = 0; i < N; i++)
        shared_array[i] = i;
        // host_array[i] = i;
    
    Q.submit([&](sycl::handler &h) {
        h.parallel_for(N, [=](sycl::id<1> i) {
            // shared_array[i] = host_array[i] + 1;
            shared_array[i]++;
        });
    });
    Q.wait();

    for (int i = 0; i < N; i++)
        std::cout << "host_array[" << i << "] = " << shared_array[i] << "\n";

    // free(host_array, Q);
    free(shared_array, Q);
    return 0;
}