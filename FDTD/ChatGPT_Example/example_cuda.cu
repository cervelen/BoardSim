// gpu_ops.cu
#include "gpu_ops.h"
#include "utils.h"
#include <cuda_runtime.h>

// CUDA kernel that performs OR reduction for double values
__global__ void any_greater_than_kernel(const double* d_data, bool* d_block_results, int N, double threshold) {
    __shared__ bool shared[256];
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int tid = threadIdx.x;

    bool gt = false;
    if (idx < N) {
        gt = d_data[idx] > threshold;
    }

    shared[tid] = gt;
    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            shared[tid] = shared[tid] || shared[tid + stride];
        }
        __syncthreads();
    }

    if (tid == 0)
        d_block_results[blockIdx.x] = shared[0];
}

// Host function that launches the kernel and returns the final result
bool anyValueGreaterThan(const double* h_data, int size, double threshold) {
    const int blockSize = 256;
    const int numBlocks = (size + blockSize - 1) / blockSize;

    // Allocate device memory
    double* d_data = nullptr;
    checkCuda(cudaMalloc(&d_data, size * sizeof(double)), "cudaMalloc d_data");
    checkCuda(cudaMemcpy(d_data, h_data, size * sizeof(double), cudaMemcpyHostToDevice), "cudaMemcpy d_data");

    // Allocate memory for block-level results
    bool* d_block_results = nullptr;
    checkCuda(cudaMalloc(&d_block_results, numBlocks * sizeof(bool)), "cudaMalloc d_block_results");

    // Launch kernel
    any_greater_than_kernel<<<numBlocks, blockSize>>>(d_data, d_block_results, size, threshold);
    checkCuda(cudaGetLastError(), "Kernel launch failed");
    checkCuda(cudaDeviceSynchronize(), "Kernel execution failed");

    // Copy back block results
    std::vector<bool> h_block_results(numBlocks);
    checkCuda(cudaMemcpy(h_block_results.data(), d_block_results, numBlocks * sizeof(bool), cudaMemcpyDeviceToHost), "Memcpy block results");

    // Final reduction on host
    bool final_result = false;
    for (bool r : h_block_results) {
        final_result = final_result || r;
    }

    // Free memory
    cudaFree(d_data);
    cudaFree(d_block_results);

    return final_result;
}
