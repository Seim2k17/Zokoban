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
    
    //TODO: recheck COLS vs. ROWS !!! -> see readLevelFromFile() ln.80: Array2D(5,7) vs. Array2D(7,5);;
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

        void setPlayerPosition(const std::pair<int,int>& curPos, const std::pair<int,int>& newPos);
        void setCurrentDirectionInput(std::pair<int,int> curInput);

        void Update(std::pair<int,int> newHeroPosition, std::pair<int,int> lastHeroPosition);
        void changeBoxPosition(int potentialRow, int potentialCol);

    private:
        void readLevelFromFile();
        void outputLevel();
        void createLevel();
        bool levelCreateable();
        TextureType getSymbolType(char& symbol);

        int _currentLevel;

        Array2D _levelData;

        std::pair<int,int> playerStartPosition;
        std::pair<int,int> currentDirectionInput;
};