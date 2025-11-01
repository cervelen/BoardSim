#ifndef FDTD_EXPERIMENT_H
#define FDTD_EXPERIMENT_H

#ifdef __CUDACC__
#define HD __host__ __device__
#define D __device__
#define H __host__
#else
#define HD
#define H
#define D
#define __global__
#endif

struct double3 {
    double x, y, z;
    
    HD double3() : x(0.0), y(0.0), z(0.0) {}
    HD double3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    
    HD double3 operator+(const double3& other) const {
        return double3(x + other.x, y + other.y, z + other.z);
    }
};

struct sphere{
    double3 origin;
    double3 rtp; //roe, theta, phi
    double3 dirvector;

    D sphere(double3 origin_, double3 rtp_, double3 dirvector_) : origin(origin_), rtp(rtp_), dirvector(dirvector_) {}
    D bool in_sphere(double3 point);
};

void launch_check_in_sphere(sphere my_sphere, double3* points, int n);






#endif