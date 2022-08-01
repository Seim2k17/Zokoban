#pragma once 

#include <string>
#include <memory>
#include "texture.h"


class Array2D;
class Level;

class Hero{

public:
    enum class Direction { kUp, kDown, kLeft, kRight };
    Hero(int grid_width, int grid_height, std::string name) 
        : grid_width(grid_width),
          grid_height(grid_height),
          _name(name) {}
    ~Hero() {};

    void Update(Array2D& levelData);
    void changeHeroTexturePosition(int x, int y, std::unique_ptr<Level>& level);
    
    TextureData getTextureData();
    std::pair<int,int> getCurrentHeroCellPosition();
    std::pair<int,int> getLastHeroCellPosition();

    void setPlayerStartPosition(std::pair<int,int>& startPosition);

private:

    int getHeroDataPosition(Array2D& levelData);
    
    std::string _name;
    
    int grid_width;
    int grid_height;

    TextureData _textureData;
};