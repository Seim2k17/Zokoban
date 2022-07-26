#pragma once 

#include <string>
#include "SDL.h"

#define HERO_TEXTURE_SIZE 32

struct TextureData {
    
    TextureData()
    {
        setSourceValues(0,0);
        setDestinationValues(0,0);
    }

    void setSourceValues(int x, int y)
    {
        Source.x = x;
        Source.y = y;
        Source.w = HERO_TEXTURE_SIZE;
        Source.h = HERO_TEXTURE_SIZE;
    }

    void setDestinationValues(int col, int row)
    {
        // set Pixelposition of texture from the position in block
        Destination.x = col*HERO_TEXTURE_SIZE;
        Destination.y = row*HERO_TEXTURE_SIZE;
        Destination.w = HERO_TEXTURE_SIZE;
        Destination.h = HERO_TEXTURE_SIZE;
        _currentCol = col;
        _currentRow = row;
    }

    SDL_Rect Source;
    SDL_Rect Destination;

    int _currentCol;
    int _currentRow;

    // TODO: refactor destroy in lambda/method, other loading in methods
    // TODO: find solution for utility methods and make
    // here getRessourcePath was used but due multiple definition issue (included in other files)
    std::string texturePath = std::string(SDL_GetBasePath())+"res/hero/" + "avatar.bmp";

};


class Hero{

public:
    enum class Direction { kUp, kDown, kLeft, kRight };
    Hero(int grid_width, int grid_height, std::string name) 
        : grid_width(grid_width),
          grid_height(grid_height),
          _name(name) {}
    ~Hero() {};

    void Update();
    TextureData getTextureData();
    void setPosition(int x, int y);
    

private:
    std::string _name;
    
    int grid_width;
    int grid_height;
  

    TextureData _textureData;
};