// main.cpp
#include <iostream>
#include <vector>
#include "gpu_ops.h"
#include "utils.h"

int main() {
    const int N = 10000;
    const double threshold = 100.0;

    // Create and fill vector on host
    std::vector<double> data(N);
    for (int i = 0; i < N; ++i) {
        data[i] = static_cast<double>(i) / 10.0;
    }

    // Uncomment to test negative case
    // data[N - 1] = 99.9;

    // Call the GPU function to check for values greater than threshold
    bool result = anyValueGreaterThan(data.data(), data.size(), threshold);

    std::cout << "Any value greater than " << threshold << "? "
              << std::boolalpha << result << std::endl;

    return 0;
}
