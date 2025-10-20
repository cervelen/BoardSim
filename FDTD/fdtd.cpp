#include "fdtd.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>



Vorp::Vorp(std::string e_or_h, std::string direction, double permeability, double starting_magnitude){
    this->e_or_h = e_or_h;
    this->direction = direction;
    this->permeability = permeability;
    this->magnitude = starting_magnitude;
    this->sim_values = {};
}

void Vorp::change_magnitude(double magnitude){
    this->magnitude = magnitude;
}



