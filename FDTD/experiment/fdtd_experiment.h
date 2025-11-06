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

#include<variant>
#include<vector>


struct double3 {
    double x, y, z;
    
    HD double3() : x(0.0), y(0.0), z(0.0) {}
    HD double3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    
    HD double3 operator+(const double3& other) const {
        return double3(x + other.x, y + other.y, z + other.z);
    }
};

struct box {
    double3 origin;
    double3 lwh;
    double3 dirvector;

    HD box(double3 origin_, double3 lwh_, double3 dirvector_) : origin(origin_), lwh(lwh_), dirvector(dirvector_) {}
    D bool in_box(double3 point);

};

struct sphere{
    double3 origin;
    double3 rtp;        //roe, theta, phi
    double3 dirvector;

    HD sphere(double3 origin_, double3 rtp_, double3 dirvector_) : origin(origin_), rtp(rtp_), dirvector(dirvector_) {}
    D bool in_sphere(double3 point);
};

void launch_check_in_sphere(sphere my_sphere, double3* points, int n);

void launch_check_in_box(box my_box, double3* points, int n);

struct vorp{
    double3 location;
    double3 dirvector;
    // vorp* 
    int h_e;            //h -> magnetic field, e -> electric field
    int material = 0;   //each material associated with a materialid, allowing the characteristics to be known for simulation (0 is free space)

    HD vorp(double3 location_, double3 dirvector_, int h_e_) : location(location_), dirvector(dirvector_), h_e(h_e_) {}


};

struct fuihua{
    std::vector<std::variant<sphere, box>> elements;    //first element is the sim box
    std::vector<vorp> yee_e_field;                       //vorps are put in vector irrespective of position
    std::vector<vorp> yee_h_field;                       //vorps are put in vector irrespective of position

    H fuihua(){};
    H bool place_box(double3 origin, double3 lwh, double3 dirvector);
    H bool place_sphere(double3 origin, double3 rtp, double3 dirvector);

    H bool generate_yee_sim_environment(double stencil_size);
};




#endif