#include "fdtd.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>

double3::double3(double x, double y, double z) : x(x), y(y), z(z) {}

double3 double3::operator+(const double3& v) const {
    return double3(x + v.x, y + v.y, z + v.z);
}

double3 double3::operator-(const double3& v) const {
    return double3(x - v.x, y - v.y, z - v.z);
}

double3 double3::operator*(double s) const {
    return double3(x * s, y * s, z * s);
}

double double3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}


Vorp::Vorp( double permeability, double e_or_h, double direction, double starting_magnitude){
    this->e_or_h = e_or_h;
    this->direction = direction;
    this->permeability = permeability;
    this->magnitude = starting_magnitude;
    this->sim_magnitudes = {};
}

void Vorp::change_magnitude(double magnitude){
    this->magnitude = magnitude;
}

E_Sim::E_Sim(std::vector<std::vector<std::vector<std::vector<double>>>> input_grid){

}

Fuihua::Fuihua(){

}

