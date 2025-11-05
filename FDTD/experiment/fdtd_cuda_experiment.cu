#include "fdtd_experiment.h"
#inclue <variant>
#include <vector>
//#include <cuda_runtime.h>



D bool box::in_box(double3 point){
    return true;
}

__global__ void check_in_box(box my_box, double3* points, int n){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        my_box.in_box(points[idx]);
    }
}

void launch_check_in_box(box my_box, double3* points, int n){
    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;
    check_in_box<<<gridSize, blockSize>>>(my_box, points, n);
    cudaDeviceSynchronize();
}

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

H bool fuihua::place_box(double3 origin, double3 lwh, double3 dirvector){
    elements.emplace_back(box(origin, lwh, dirvector));
    return true;
}

H bool fuihua::place_sphere(double3 origin, double3 rtp, double3 dirvector){
    elements.emplace_back(sphere(origin, rtp, dirvector));
    return true;
}

H bool fuihua::generate_yee_sim_environment(){
    if (!elements.empty()){
        if (std::holds_alternative<Sphere>(elements[0])) {
            
        } else if (std::holds_alternative<Box>(elements[0])) {
            
        }
    }

}