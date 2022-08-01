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

bool
Hero::boxMovable(int row, int col,std::unique_ptr<Level>& level)
{
    TextureType type = level->getLevelData()[row][col].texture.type;
    if(type != TextureType::Wall && type != TextureType::Box)
    {
        return true;
    }

    return false;
}

bool
Hero::playerBlocked(int row, int col, int dirRow, int dirCol, std::unique_ptr<Level>& level)
{
    TextureType type = level->getLevelData()[row][col].texture.type;

    switch(type)
    {
        case TextureType::Wall:
            return true;
        case TextureType::Box:
        {
            // is box movable to the direcdtion the player pushes?
            return !(boxMovable(row+dirRow,col+dirCol,level));
        }
            
        default:
            return false;
    }
}

PossiblePush
Hero::changeHeroTexturePosition(int dirRow, int dirCol, std::unique_ptr<Level>& level)
{
    //
    int potentialY = _textureData.currentLocation.first+dirRow;
    int potentialX = _textureData.currentLocation.second+dirCol;
    PossiblePush box;

    if(!playerBlocked(potentialY,potentialX,dirRow,dirCol,level))
    {
      _textureData.setDestinationValues(potentialY,potentialX);
      // here it means we can make a potential push
      box = {true,potentialY+dirRow,potentialX+dirCol};
    }
    
    return box;
}