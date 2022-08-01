# CPPND: Capstone Zokoban


This is the final project (Capstone project) for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The basis for this repo was used from the CPPND: Capstone Snake Game Example (git@github.com:udacity/CppND-Capstone-Snake-Game.git).


WIP

Zokoban is a remake of the european 1984 sokoban game created by Hiroyuki Imabayashi in or until 1982.

Nice to read: http://www.games4brains.de/sokoban-geschichte.php

Game Requirements

(- basic Ui (menu start,end,options, select level))
- enter name and use it through the game for avatar
- some self drawn pixelart assets (first dummy assets)

DONE:

- walk u,d,l,r
- create levels from input files (ASCII based)
- goal area

TODO:
-> cp assets to the build folder ! / create build/assets folder ...
- input name or level to load at beginning (The project accepts input from a user as part of the necessary operation of the program.)
- if boxes are blocked show hint that solving is impossible 
-> restart level
- detect collision for boxes (almost done) -> see rubric
- All class members that are set to argument values are initialized through member initialization lists.


- push boxes if possible (no wall)
(- use simple sounds)
- opponent ("cpu-ai") solving the same puzzle using pathfinding (A*) running in seperate thread / steals boxes & put them in other random places? -> need to solve the puzzle before opponent steals a box / one need jail the opponent with other boxes so stealing is not possible --> then solve the puzzle
- show time needed
- show boxes left
- show movecounter, pushcounter updates 
- when level finished show results (resultscreen)
(for time and design reason use level layouts from the original game)



The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * on Ubuntu/Debian like systems its "sudo apt install libsdl2-dev"
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Copy folder /res to /build: ../build: cp -r ../res .
4. Run it: `./Zokoban`.

## Ressources

1. SDL tutorials: https://www.willusher.io/pages/sdl2/
2. https://wiki.libsdl.org/
3. Sokoban levels: http://borgar.net/programs/sokoban/#Sokoban
4. SDL Keys: https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
