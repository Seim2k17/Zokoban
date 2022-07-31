#include "hero.h"
// TODO: outsource Array2D to extra file (no references to level from here)
#include "level.h"
#include <vector>
#include <iostream>

TextureData
Hero::getTextureData()
{
    return _textureData;
}

void
Hero::Update(Array2D& levelData)
{
    convertHeroPosition(getHeroDataPosition(levelData), levelData._rows, levelData._blocks.size());
    

}

int 
Hero::getHeroDataPosition(Array2D& levelData)
{
    int i=0;
    for(auto const& block:levelData._blocks)
    {
        if(block == 'P')
        {
            return i;
        }
        ++i;
    }

    return '?'; /// no Playerblock found
}

std::pair<int,int>
Hero::getCurrentHeroCellPosition()
{
    return _textureData.currentLocation;
}

std::pair<int,int>
Hero::getLastHeroCellPosition()
{
    return _textureData.lastLocation;
}

void
Hero::convertHeroPosition(int currentPosition, int rows, int levelDataSize)
{


    /* TODO overthink
     _textureData._currentCol= currentPosition / rows;
    _textureData._currentRow = currentPosition % rows ;
    */

    // TODO: convert correctly AND setPositionTexture from beginning
    //std::cout << "PlayerPos:" << currentPosition << "," << rows << std::endl; 
    //std::cout << "PlayerPos(conv): (" << _textureData._currentCol << "," << _textureData._currentRow << ")" << std::endl; 
    //std::cout << "gridH: " << grid_height << "gridW: " << grid_width << std::endl;

}

void
Hero::changeHeroTexturePosition(int x, int y)
{
    _textureData.setDestinationValues(_textureData.currentLocation.first+x,_textureData.currentLocation.second+y);
}