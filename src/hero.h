#pragma once 

#include <string>

class Hero{

public:
    enum class Direction { kUp, kDown, kLeft, kRight };
    Hero(int grid_width, int grid_height, std::string name) 
        : grid_width(grid_width),
          grid_height(grid_height),
          _name(name) {}
    ~Hero() {};

    void Update();

private:
    std::string _name;
    int grid_width;
    int grid_height;
};