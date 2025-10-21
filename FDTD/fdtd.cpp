#include "fdtd.h"
#include "fdtd_cuda.h"
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
    // for (int layer = 0; layer < input_grid.size(); layer++){
    //     this->grid[layer].push_back({});
    //     for (int row = 0; row < input_grid[layer].size(); row++){
    //         this->grid[layer][row].push_back({});
    //         for (int vorp = 0; vorp < input_grid[layer][row].size(); vorp++){
    //             this->grid[layer][row].emplace_back(Vorp(input_grid[layer][row][vorp][0], input_grid[layer][row][vorp][1], input_grid[layer][row][vorp][2], 0));
    //         }
    //     }
    // }
    //construction above
    //validation below
    //validation above
}

Fuihua::Fuihua(const std::string& simulation_type, double voxel_scalar){
    this->simulation_type = simulation_type;
    this->voxel_scalar = voxel_scalar;
    this->face_ids = {};
    this->voxelized_grid_size = {0.0, 0.0, 0.0};

    std::vector<std::vector<double>> sim_object = {};
    this->simulation_object = sim_object;
    std::vector<std::vector<std::vector<double>>> vox_grid = {};
    this->voxelized_grid = vox_grid;
}

void Fuihua::generate_material(double material_positive, double material_negative, std::vector<std::vector<double>>& faces){
    //initial pass
    if (face_ids.empty() == true){
        for (int face = 0; face < faces.size(); face++){
            face_ids.push_back(static_cast<double>(face));

            double* numerator = faces[face].data();         //generates array to be passed into function

            std::vector<double> denominator_vector(faces[face].size(), voxel_scalar);
            double* denominator = denominator_vector.data();

            std::vector<double> result_vector(faces[face].size(), 0.0);
            double* result = result_vector.data();

            divide_vectors(numerator, denominator, result, result_vector.size());


        }
    }

}