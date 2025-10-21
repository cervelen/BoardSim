// utils.h
#pragma once
#include <iostream>
#include <cuda_runtime.h>

// Simple CUDA error checker
inline void checkCuda(cudaError_t err, const char* msg) {
    if (err != cudaSuccess) {
        std::cerr << msg << ": " << cudaGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}
