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





#endif // FDTD_H