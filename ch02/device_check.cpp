#include <CL/sycl.hpp>
#include <iostream>
#include <string>

namespace sycl = cl::sycl;

void output_device_info(const sycl::device& dev, const std::string& selector_name) {
    std::cout << selector_name << ": Selected device: " << dev.get_info<sycl::info::device::name>() << "\n";
    std::cout << "    -> Device vendor: " << dev.get_info<sycl::info::device::vendor>() << "\n";
}

int main() {
    output_device_info( sycl::device {sycl::default_selector{}}, "default_selector");
    output_device_info( sycl::device {sycl::host_selector{}}, "host_selector");
    output_device_info( sycl::device {sycl::cpu_selector{}}, "cpu_selector");
    output_device_info( sycl::device {sycl::gpu_selector{}}, "gpu_selector");
    // output_device_info( sycl::device {sycl::accelerator_selector{}}, "accelerator_selector");
}
