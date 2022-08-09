#include "level.h"
//#include "resource_path.h"
#include "texture.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <string_view>
#include <SDL.h>


constexpr std::string_view levelPath{"res/level/"};


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
Level::checkWinCondition(bool &condition)
{
    //std::cout << "Check winstate: " << _remainingGoalCounter << " boxes left." << std::endl;
    if(_remainingGoalCounter == 0 && !condition)
    {
        std::cout << "You won the level!" << std::endl;
        condition=true;
    }
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
    //t.b.d.
}

void
Level::setPlayerPosition(const std::pair<int,int>& newPos, const std::pair<int,int>& lastPos,const std::pair<int,int>& direction, bool pushing)
{
    // TODO : Refactor deluxe !
    char &lastPosiSymbol = _levelData[lastPos.first][lastPos.second].characterSymbol;
    char &newPosiSymbol = _levelData[newPos.first][newPos.second].characterSymbol;
    

    TextureType potentialPosiSymbol = getSymbolType(newPosiSymbol);

    switch(potentialPosiSymbol)
    {
        case TextureType::Wall:
            break;
        case TextureType::Box:
        {
            if(pushing)
            {
                char &newBoxPosiSymbol = _levelData[newPos.first+direction.first][newPos.second+direction.second].characterSymbol;
                char &lastBoxPosiSymbol = _levelData[newPos.first][newPos.second].characterSymbol;
                if(_levelData[lastPos.first][lastPos.second].savedSymbol == '.')
                {
                    lastPosiSymbol = '.';
                    _levelData[lastPos.first][lastPos.second].savedSymbol == ' ';
                }
                else
                {
                    lastPosiSymbol = ' ';
                    _levelData[lastPos.first][lastPos.second].texture.type = TextureType::Empty;
                }
                
                lastBoxPosiSymbol = 'P';
                _levelData[newPos.first][newPos.second].texture.type = TextureType::Player;
                if(newBoxPosiSymbol == '.')
                {
                    --_remainingGoalCounter;
                }
                newBoxPosiSymbol ='B';
                _levelData[newPos.first+direction.first][newPos.second+direction.second].texture.type = TextureType::Box;
            }
            break;
        }
        case TextureType::Goal:
        {
            _levelData[newPos.first][newPos.second].savedSymbol = '.';
            if(_levelData[lastPos.first][lastPos.second].savedSymbol == '.')
            {
                lastPosiSymbol = '.';
                _levelData[lastPos.first][lastPos.second].texture.type = TextureType::Goal;
            }
            else{
                lastPosiSymbol = ' ';
                _levelData[lastPos.first][lastPos.second].texture.type = TextureType::Empty;
            }
            
            newPosiSymbol = 'P';
            _levelData[newPos.first][newPos.second].texture.type = TextureType::Player;
            break;
        }
        default:
            {
                if(_levelData[lastPos.first][lastPos.second].savedSymbol == '.')
                {
                    lastPosiSymbol = '.';
                    _levelData[lastPos.first][lastPos.second].texture.type = TextureType::Goal;
                    _levelData[lastPos.first][lastPos.second].savedSymbol == ' ';
                }
                else
                {
                    lastPosiSymbol = ' ';
                    _levelData[lastPos.first][lastPos.second].texture.type = TextureType::Empty;
                }
                newPosiSymbol = 'P';
                _levelData[newPos.first][newPos.second].texture.type = TextureType::Player;
                break;
            }
    }
    outputLevel();
}

int
Level::getMaxLevelCount(const std::string path)
{
    auto dirIt = std::filesystem::directory_iterator(path);
    int count = std::count_if(
        begin(dirIt),
        end(dirIt),
        [](auto& entry){ 
            auto found = std::string(entry.path()).find("level_");
            std::cout << std::string(entry.path()) << ": " << found << std::endl;
            return (entry.is_regular_file() && (found != std::string::npos));
        }
    );
    return count;
}

std::pair<int,int>
Level::readLevelSizeFromFile()
{
    const std::string fullPath = std::string(SDL_GetBasePath())+ std::string(levelPath) + "level_" +std::to_string(_currentLevel);
    char character;
    std::string line;
    std::pair<int,int> size{0,0};
    std::ifstream filestream(fullPath);

    std::cout << "Files found: " << getMaxLevelCount(std::string(SDL_GetBasePath())+std::string(levelPath)) << std::endl;
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            if(size.second < line.size())
            {
                size.second = line.size();
            }
            
            ++size.first;
        }
    }
    std::cout << "size of file for level " << size.first << ":" << size.second << std::endl;
    return size;
}


void
Level::readLevelFromFile()
{
    const std::string fullPath = std::string(SDL_GetBasePath())+ std::string(levelPath) + "level_"+ std::to_string(_currentLevel);

    std::string line;
    char symbol;
    int row=0,col=0;

    std::pair<int,int> levelSize = readLevelSizeFromFile();
    _levelData = Array2D(levelSize.second,levelSize.first);
    
    // TODO: check in debugmode if everythinig is filled correctly
    // -> Texture and Data in the same datastructure !!! at reading the level
    // -> so that later in best case only a lookup is needed

    
  
    std::ifstream filestream(fullPath);
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
                if(_levelData[row][col].texture.type == TextureType::Goal)
                {
                    ++_remainingGoalCounter;
                }
                ++col;
            }
            ++row;
        }
    }
    else
    {
        std::cout << "Cannot open file " << fullPath << std::endl;
    }
    std::cout << "Done reading LevelData: ReOutput Level" << std::endl;
    outputLevel();
}

void
Level::outputLevel()
{
    int rows = _levelData._rows;
    int cols = _levelData._blocks.size() / rows;
    
    // WHY +1 ???
    for(int j=0;j<rows+1;++j)
    {
        for(int i=0;i<cols+1;++i)
        {
            printf("%c",_levelData[j][i].characterSymbol);
        }
        printf("%s","\n");
    }
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
Level::changeBoxPosition(int boxRow, int boxCol,std::pair<int,int> direction)
{
    _levelData[boxRow][boxCol].texture.setDestinationValues(boxRow+direction.first,boxCol+direction.second);
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