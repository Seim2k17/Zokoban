#include "hero.h"

TextureData
Hero::getTextureData()
{
    return _textureData;
}

void
Hero::Update()
{

}

void
Hero::setPosition(int x, int y)
{
    _textureData.setDestinationValues(_textureData._currentCol+x,_textureData._currentRow+y);
}