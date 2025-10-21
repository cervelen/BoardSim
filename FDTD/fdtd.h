#ifndef FDTD_H
#define FDTD_H

#include <vector>

class Vorp{
    public:
        double e_or_h;              //classify whether an E field value or H field value. 0 -> E, 1 -> H.
        double direction;           //direction the E or H field is referenced. 1 -> x, 2 -> y, 3 -> z.
        double permeability;        //permeability of the material, of which this point is a part.
        double magnitude;           //magnitude that changes as the field changes.
        std::vector<double> sim_magnitudes;

        Vorp(double e_or_h, double direction, double permeability, double magnitude);
        void change_magnitude(double magnitude);

};

class E_Sim{
    public:
        std::vector<std::vector<std::vector<Vorp>>> grid;   //each vorp in the grid is separated by 1/2 cell from each other vorp.
        

        E_Sim(std::vector<std::vector<std::vector<std::vector<double>>>> input_grid); //each 3rd depth vector has 3 doubles: 0th -> permeability, 1st -> E or H, 2nd -> direction. 
};

class Fuihua{
    public:
        //the simulation object is a 3d shape that has varying materials enclosed within.
        //Each 1st depth vector is a face.
        //each face is created by a vector of doubles, where:
        //0th index: material normal positive to the surface.
        //1st index: material normal negative to the surface.
        //material 0 will ALWAYS be outside the simulation environment.
        //4th index: number of vertices.
        //3rd-11th+ index:  xyz, xyz, xyz... of each vertex. 
        //xyz location will always be spatially in METERS.
        //if you want to avoid bad values, normalize your neural network, NOT the simulation. This is done for accuracies sake.
        //vertices are all connected in a clockwise pattern when looking from above (looking in the negative direction).
        //boundary oriented simulation. 
        //The material normal positive to EVERY face in the environment box is the same, and the boundary MUST encompass everything being simulated.
        //This massive object is done to preserve efficiency of simulation.
        //I implore you to play around and make things PARAMETRICALLY.
        //don't forget to have fun and be creative, make machines, advance humanity, and support your community.
        std::vector<std::vector<double>> simulation_object;
        std::string simulation_type;

        Fuihua(std::string simulation_type);

        //if a generated material overlaps with another, it overwrites that material inherently.
        //The order of material generation will determine the object -> simulation conversion.

        //this function is for building with your own sim environment, and meant to be used the most.
        void generate_material(double material_positive, double material_negative, std::vector<std::vector<double>> vertices);

        //these below are for QOL and tutorials
        void generate_box(double origin_x, double origin_y, double origin_z, double length, double width, double height); //x -> length, y -> width, z -> height
        void generate_sphere(double origin_x, double origin_y, double origin_z, double r, double theta, double phi); 

        //Below, each punch is represented in the same way as a face, but without material (since there is no material there).
        //First face is outside punch, each additional is a hole in the plate.
        //this function is meant for simulations of traditional layered PCBs. 
        void generate_plate(double origin_x, double origin_y, double origin_z, std::vector<std::vector<double>> punches); 


};





#endif // FDTD_H