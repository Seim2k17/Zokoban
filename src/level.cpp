#include "level.h"
//#include "resource_path.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
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

bool
Level::levelCreateable()
{
    //TODO: implement if current level is possible to create with the given level structure in the level file
    return true;
}

void
Level::readLevelFromFile()
{
    // see also render.cpp
    //const std::string levelPath = getResourcePath("level") + "level_" + std::to_string(_currentLevel);
    const std::string levelPath = std::string(SDL_GetBasePath())+"res/level/" + "level_" + std::to_string(_currentLevel);

    std::string line;
    char symbol;
    int row=0,col=0;

    _levelData = Array2D(5,7);
  
    std::ifstream filestream(levelPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            std::cout << line << std::endl;
            col=0;
            linestream >> std::noskipws; /// whitspace are not ignored, otherwise the data vector holds wrong level data
            while(linestream >> symbol)
            {
                _levelData[row][col] = symbol;
                ++col;
            }
            ++row;
        }
    }
    else
    {
        std::cout << "Cannot open file " << levelPath << std::endl;
    }
    std::cout << "Done reading LevelData" << std::endl;

}

int
Level::getCurrentLevel()
{
    return _currentLevel;
}