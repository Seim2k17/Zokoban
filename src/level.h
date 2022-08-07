#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "texture.h"

using std::vector;

struct LevelBlock{
    // symbol representing the levelblock in text
    char characterSymbol;
    // saved symbol
    char savedSymbol;
    // texture representiung the levelblock visually
    TextureData texture;
    // position of the levelblock in the levelgrid
    std::pair<int,int> position;

};

class Array2D {
    
    //TODO: recheck COLS vs. ROWS !!! -> see readLevelFromFile() Array2D(5,7) vs. Array2D(7,5);;
    public:
        Array2D(){};
        Array2D(int rows, int cols)
            : _blocks(rows*cols),
            _rows(rows) {}
        
        LevelBlock* operator[](int el) { return &_blocks[el*_rows];}

        vector<LevelBlock> _blocks;
        int _rows;
        
};

class Level
{
    public:
        Level(int level);
        ~Level();

        Array2D& getLevelData();
        std::vector<LevelBlock> getLevelBlocks();
        int getCurrentLevel();
        std::pair<int,int>& getPlayerStartPosition();

        void setPlayerPosition(const std::pair<int,int>& curPos, const std::pair<int,int>& newPos,const std::pair<int,int>& direction, bool pushing);
        void setCurrentDirectionInput(std::pair<int,int> curInput);

        void Update(std::pair<int,int> newHeroPosition, std::pair<int,int> lastHeroPosition);
        void changeBoxPosition(int boxRow, int boxCol,std::pair<int,int> direction);
        void checkWinCondition(bool &condition);

    private:
        void readLevelFromFile();
        std::pair<int,int> readLevelSizeFromFile();
        void outputLevel();
        void createLevel();
        bool levelCreateable();
        int getMaxLevelCount(const std::string path);
        TextureType getSymbolType(char& symbol);

        int _currentLevel;

        Array2D _levelData;

        std::pair<int,int> playerStartPosition;
        std::pair<int,int> currentDirectionInput;

        int _remainingGoalCounter{0};
};