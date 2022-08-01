#pragma once

#include "SDL.h"

#define TEXTURE_SIZE 32

enum class TextureType {Empty,Player,Wall,Box,Goal};

struct TextureData {
    
    // TODO: check to generalize this with leveldata into renderer ?
    TextureData()
    {
        setSourceValues(0,0);
        setDestinationValues(0,0);
        type = TextureType::Empty;
    }

    void setSourceValues(int x, int y)
    {
        Source.x = x;
        Source.y = y;
        Source.w = TEXTURE_SIZE;
        Source.h = TEXTURE_SIZE;
    }

    void setDestinationValues(int row, int col)
    {
        // set Pixelposition of texture from the position in block
        Destination.x = (col)*TEXTURE_SIZE;
        Destination.y = (row)*TEXTURE_SIZE;
        Destination.w = TEXTURE_SIZE;
        Destination.h = TEXTURE_SIZE;
        
        lastLocation.first = currentLocation.first;
        lastLocation.second = currentLocation.second;
        
        currentLocation.first = row;
        currentLocation.second = col;
    }

    SDL_Rect Source;
    SDL_Rect Destination;

    TextureType type;

    std::pair<int,int> currentLocation{0,0};
    std::pair<int,int> lastLocation{0,0};
};