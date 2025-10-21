int main() {
    const int N = 10000;              // Size of input array
    double threshold = 100.0;         // Value to compare against

    // Allocate and initialize host array
    double* h_data = new double[N];
    for (int i = 0; i < N; ++i)
        h_data[i] = static_cast<double>(i) / 10.0;  // e.g. 0.0, 0.1, ..., 999.9

    // Optional: to test the "false" case, uncomment this line
    // h_data[N - 1] = 99.9;  // Ensures all elements are below the threshold

    // Allocate device memory for input array
    double* d_data;
    checkCuda(cudaMalloc(&d_data, N * sizeof(double)), "cudaMalloc d_data");

    // Copy data from host to device
    checkCuda(cudaMemcpy(d_data, h_data, N * sizeof(double), cudaMemcpyHostToDevice), "cudaMemcpy d_data");

    // Configure kernel launch parameters
    const int blockSize = 256;  // Number of threads per block
    const int numBlocks = (N + blockSize - 1) / blockSize;  // Total number of blocks needed

    // Allocate memory to store one bool result per block
    bool* d_block_results;
    checkCuda(cudaMalloc(&d_block_results, numBlocks * sizeof(bool)), "cudaMalloc d_block_results");

    // Launch the CUDA kernel to compare and reduce within each block
    any_double_greater_than<<<numBlocks, blockSize>>>(
        d_data, d_block_results, N, threshold
    );
    checkCuda(cudaGetLastError(), "Kernel launch failed");

    // Allocate host memory to retrieve block-level results
    bool* h_block_results = new bool[numBlocks];

    // Copy results from device to host
    checkCuda(cudaMemcpy(h_block_results, d_block_results, numBlocks * sizeof(bool), cudaMemcpyDeviceToHost), "Memcpy block results");

    // Final OR reduction on the host across all block results
    bool final_result = false;
    for (int i = 0; i < numBlocks; ++i)
        final_result = final_result || h_block_results[i];

    // Print the final result
    std::cout << "Any value greater than " << threshold << "? " << std::boolalpha << final_result << std::endl;

    // Cleanup device and host memory
    cudaFree(d_data);
    cudaFree(d_block_results);
    delete[] h_data;
    delete[] h_block_results;

    return 0;
}
