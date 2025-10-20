#ifndef FDTD_H
#define FDTD_H

#include <vector>

class Vorp{
    public:
        std::string e_or_h;         //classify whether an E field value or H field value
        std::string direction;      //direction the E or H field goes
        double permeability;        //permeability of the material this point is a part of
        double magnitude;
        std::vector<double> sim_values;

        Vorp(std::string e_or_h, std::string direction, double permeability, double magnitude);
        void change_magnitude(double magnitude);

};

class E_Sim{
    public:
        std::vector<std::vector<std::vector<Vorp>>> grid;   //each vorp in the grid is separated by 1/2 cell from each other vorp.
        

        E_Sim(std::vector<std::vector<std::vector<double>>> )
};




#endif // FDTD_H