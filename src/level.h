#pragma once

#include <iostream>
#include <vector>
#include <string>

using std::vector;

class Array2D {
    
    public:
        Array2D(){};
        Array2D(int rows, int cols)
            : _blocks(rows*cols),
            _rows(rows) {}
        
        char* operator[](int el) { return &_blocks[el*_rows];}

        vector<char> _blocks;
        int _rows;
        
};

class Level
{
    public:
        Level(int level);
        ~Level();

        Array2D& getLevelData();

        void Update(std::pair<int,int> newHeroPosition, std::pair<int,int> lastHeroPosition);

        int getCurrentLevel();
        void setPlayerPosition(const std::pair<int,int>& curPos, const std::pair<int,int>& newPos);
        void setCurrentDirectionInput(std::pair<int,int> curInput);
    
    private:
        void readLevelFromFile();
        void outputLevel();
        void createLevel();
        bool levelCreateable();

        int _currentLevel;

        Array2D _levelData;

        std::pair<int,int> currentDirectionInput;
};