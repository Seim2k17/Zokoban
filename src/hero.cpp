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
    //t.b.d. (StateMachione for box etc ?)
}

int 
Hero::getHeroDataPosition(Array2D& levelData)
{
    int i=0;
    for(auto const& block:levelData._blocks)
    {
        if(block.characterSymbol == 'P')
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
Hero::setPlayerStartPosition(std::pair<int,int> &startPosition)
{
    _textureData.setDestinationValues(startPosition.first,startPosition.second);
}

void
Hero::changeHeroTexturePosition(int x, int y, std::unique_ptr<Level>& level)
{
    //TODOD: OMG is this creepy
    if(level->getLevelData()[_textureData.currentLocation.first+x][_textureData.currentLocation.second+y].texture.type != TextureType::Wall)
    {
      _textureData.setDestinationValues(_textureData.currentLocation.first+x,_textureData.currentLocation.second+y);
    }
    
}