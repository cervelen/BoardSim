#include "fdtd.h"
#include <cuda_runtime.h>

struct sphere{
    
}
__global__ void divide_kernel(double* numerator, double* denominator, double* result, int size){ //each vector is the same size
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < size){
        if (denominator[idx] != 0.0) {
            result[idx] = numerator[idx] / denominator[idx];
        } else {
            result[idx] = 0.0;
        }
    }
}
void divide_vectors(double* numerator, double* denominator, double* result, int size){

    //allocates memory on the CUDA side
    double *d_numerator, *d_denominator, *d_result;
    cudaMalloc(&d_numerator, size * sizeof(double));
    cudaMalloc(&d_denominator, size * sizeof(double));
    cudaMalloc(&d_result, size * sizeof(double));

    //copies values from host to cuda device
    cudaMemcpy(d_numerator, numerator, size * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_denominator, denominator, size * sizeof(double), cudaMemcpyHostToDevice);

    //generates number of blocks needed for division of all doubles
    int threadsPerBlock = 128;
    int numBlocks = (size + threadsPerBlock - 1) / threadsPerBlock;

    //runs divide_kernel
    divideKernel<<<numBlocks, threadsPerBlock>>>(d_numerator, d_denominator, d_result, size);

    //copies memory back to host
    cudaMemcpy(result, d_result, size * sizeof(double), cudaMemcpyDeviceToHost);
    
    //cleans up cuda memory
    cudaFree(d_numerator);
    cudaFree(d_denominator);
    cudaFree(d_result);


}