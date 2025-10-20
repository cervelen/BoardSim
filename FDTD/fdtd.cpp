#include "fdtd.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>



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

    //Construction below
    for (int layer = 0; layer < input_grid.size(); layer++){
        this->grid[layer].push_back({});
        for (int row = 0; row < input_grid[layer].size(); row++){
            this->grid[layer][row].push_back({});
            for (int vorp = 0; vorp < input_grid[layer][row].size(); vorp++){
                this->grid[layer][row].emplace_back(Vorp(input_grid[layer][row][vorp][0], input_grid[layer][row][vorp][1], input_grid[layer][row][vorp][2], 0));
            }
        }
    }
    //construction above
    //validation below
    for (int layer = 0; layer < input_grid.size(); layer++){
        for (int row = 0; row < input_grid[layer].size(); row++){
            for (int vorp = 0; vorp < input_grid[layer][row].size(); vorp++){
                this->grid[layer][row].emplace_back(Vorp(input_grid[layer][row][vorp][0], input_grid[layer][row][vorp][1], input_grid[layer][row][vorp][2], 0));
            }
        }
    }


}


