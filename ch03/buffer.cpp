#include <CL/sycl.hpp>
#include <array>

namespace sycl = cl::sycl;
constexpr int N = 42;

int main() {
    std::array<int, N> my_data;

    for (int i = 0; i < N; i++)
        my_data[i] = 0;
    
    {
        sycl::queue Q;
        sycl::buffer my_buffer(my_data);

        Q.submit([&](sycl::handler &h) {
            sycl::accessor my_accessor(my_buffer, h);

            h.parallel_for(N, [=](sycl::id<1> i) {
                my_accessor[i]++;
            });
        });

        sycl::host_accessor host_accessor(my_buffer);

        for (int i = 0; i < N; i++) {
            std::cout << host_accessor[i] << " ";
        }
        std::cout << "\n";
    }

    // buffer destroyed & my_data will be updated
    for (int i = 0; i < N; i++)
        std::cout << my_data[i] << " ";

    std::cout << "\n";
}