#include "SmartPtr.h"
#include <iostream>
#include <chrono>
#include <vector>

struct Dummy {
    int data[100];
};

int main() {
    const size_t N = 1000000;
    std::vector<SmrtPtr<Dummy>> vec;
    vec.reserve(N);

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < N; ++i) {
        vec.emplace_back(new Dummy());
    }

    auto mid = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < N; ++i) {
        vec[i] = nullptr; // release
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> alloc_time = mid - start;
    std::chrono::duration<double> release_time = end - mid;

    std::cout << "Allocated " << N << " objects in " << alloc_time.count() << " s\n";
    std::cout << "Released " << N << " objects in " << release_time.count() << " s\n";

    return 0;
}
