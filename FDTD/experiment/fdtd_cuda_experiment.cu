#include "fdtd_experiment.h"
//#include <cuda_runtime.h>



D bool sphere::in_sphere(double3 point){
    return true;
}

__global__ void check_in_sphere(sphere my_sphere, double3* points, int n){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        my_sphere.in_sphere(points[idx]);
    }
}

void launch_check_in_sphere(sphere my_sphere, double3* points, int n){
    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;
    check_in_sphere<<<gridSize, blockSize>>>(my_sphere, points, n);
    cudaDeviceSynchronize();
}