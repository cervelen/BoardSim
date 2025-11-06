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

H bool fuihua::generate_yee_sim_environment(double stencil_size){
    if (!elements.empty()){
        if (std::holds_alternative<sphere>(elements[0])) {
            
        } else if (std::holds_alternative<box>(elements[0])) {
            for (int i = 0; i < static_cast<int>((elements[0].lwh.z)/stencil_size); i++){          //*UNDER CONSTRUCTION*
                for (int j = 0; j < static_cast<int>((elements[0].lwh.y)/stencil_size); j++){      //obviously stencil size is not factored in here <-^-∨
                    for (int k = 0; k < static_cast<int>((elements[0].lwh.x)/stencil_size); k++){  //*UNDER CONSTRUCTION*
                        yee_e_field.emplace_back(vorp(double3(double(stencil_size), double(stencil_size), double(stencil_size)), double3(double(), double(), double()), int()));
                        yee_h_field.emplace_back(vorp(double3(double(stencil_size), double(stencil_size), double(stencil_size)), double3(double(), double(), double()), int()));
                    }
                }
            }
        }
    }

}