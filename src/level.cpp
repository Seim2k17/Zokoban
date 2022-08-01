#include "level.h"
//#include "resource_path.h"
#include "texture.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string_view>
#include <SDL.h>

constexpr std::string_view levelPath{"/level"};

Level::Level(int level)
    : _currentLevel(level)
{
    std::cout << "Level ctor: Level " << _currentLevel <<  std::endl;
    createLevel();
}

Level::~Level()
{
    std::cout << "Level dtor: Level " << _currentLevel << std::endl;
}

Array2D& 
Level::getLevelData()
{
    return _levelData;
}

void
Level::createLevel()
{
    readLevelFromFile();

    if(levelCreateable())
    {

    }
    else
    {
        std::cout << "Level " << _currentLevel <<" not creatable with the given level-file" << std::endl;
    }
}

std::vector<LevelBlock>
Level::getLevelBlocks()
{
    return _levelData._blocks;
}

bool
Level::levelCreateable()
{
    //TODO: implement if current level is possible to create with the given level structure in the level file
    return true;
}

void
Level::Update(std::pair<int,int> newHeroPosition, std::pair<int,int> lastHeroPosition)
{
    //TODO: levelstuff t.b.d.
    if(currentDirectionInput.first != 0 || currentDirectionInput.second != 0)
    {
        std::cout << "Hero was at: (" << lastHeroPosition.first << "," << lastHeroPosition.second << ")" << std::endl;
        std::cout << "Hero is at: (" << newHeroPosition.first << "," << newHeroPosition.second << ")" << std::endl;
        std::cout << "CurDirInput: (" << currentDirectionInput.first << "," << currentDirectionInput.second << ")" << std::endl;
        setPlayerPosition(newHeroPosition,lastHeroPosition);
    }
    
}

void
Level::readLevelFromFile()
{
    const std::string levelPath = std::string(SDL_GetBasePath())+"res/level/" + "level_" + std::to_string(_currentLevel);

    std::string line;
    char symbol;
    int row=0,col=0;

    // TODO set size acc. to levelfile ! NO MAGIC NUMBERS
    _levelData = Array2D(7,5);
  
    std::ifstream filestream(levelPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            std::cout << line << std::endl;
            col=0;
            linestream >> std::noskipws; /// whitspace are not ignored, otherwise the data vector holds wrong level data
            while(linestream >> symbol)
            {
                _levelData[row][col].characterSymbol = symbol;
                _levelData[row][col].texture.setDestinationValues(row,col);
                _levelData[row][col].texture.type = getSymbolType(symbol);
                // as the player is created separately we set here the correct start position
                if(_levelData[row][col].texture.type == TextureType::Player)
                {
                    playerStartPosition.first = row;
                    playerStartPosition.second = col;
                }
                ++col;
            }
            ++row;
        }
    }
    else
    {
        std::cout << "Cannot open file " << levelPath << std::endl;
    }
    std::cout << "Done reading LevelData: ReOutput Level" << std::endl;
    outputLevel();
}

void
Level::outputLevel()
{
    int rows = _levelData._rows;
    int cols = _levelData._blocks.size() / rows;
    
    //WHY +1 ???
    for(int j=0;j<=rows+1;++j)
    {
        for(int i=0;i<=cols+1;++i)
        {
            printf("%c",_levelData[j][i].characterSymbol);
        }
        printf("%s","\n");
    }
}

void
Level::setPlayerPosition(const std::pair<int,int>& newPos, const std::pair<int,int>& lastPos)
{
    // TODO some checks if there are special areas/boxes/walls at the new position then block or st else ....
    // think of if this is now the point to introduce a small state machine ?
    char& lastPosiSymbol = _levelData[lastPos.first][lastPos.second].characterSymbol;
    char& newPosiSymbol = _levelData[newPos.first][newPos.second].characterSymbol;

    if((getSymbolType(newPosiSymbol) != TextureType::Wall) 
        && (getSymbolType(newPosiSymbol) != TextureType::Box))
    {
        lastPosiSymbol = ' ';
        newPosiSymbol = 'P';
    }
    
    outputLevel();

}

std::pair<int,int>&
Level::getPlayerStartPosition()
{
    return playerStartPosition;
}

TextureType
Level::getSymbolType(char& symbol)
{
    switch(symbol)
    {
        case 'P':
            return TextureType::Player;
        case '#':
            return TextureType::Wall;
        case 'B':
            return TextureType::Box;
        case '.':
            return TextureType::Goal;
        default:
            return TextureType::Empty;
    }
    return TextureType::Empty;
}

void
Level::setCurrentDirectionInput(std::pair<int,int> curInput)
{
    currentDirectionInput = curInput;
}

int
Level::getCurrentLevel()
{
    return _currentLevel;
}