#pragma once

#include <iostream>
#include <vector>
#include <string>

using std::vector;

class Array2D {
    
    public:
        Array2D(){};
        Array2D(int cols, int rows)
            : _blocks(cols*rows),
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

        int getCurrentLevel();
    
    private:
        void readLevelFromFile();
        void createLevel();
        bool levelCreateable();

        int _currentLevel;

        Array2D _levelData;
};