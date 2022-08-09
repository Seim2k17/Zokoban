# Udacity C++ Capstone Project: Zokoban


This is the final project (Capstone project) for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). This project goes with Capstone option 2 (clone a classic 2D game). The basis for this repo was used from the [CPPND: Capstone Snake Game Example](https://github.com/udacity/CppND-Capstone-Snake-Game).

Zokoban is a remake of the european 1984 sokoban game created by Hiroyuki Imabayashi in or until 1982.
In this 2D-puzzle-game you are a warehouseman and you need to push all boxes to the correct position. You can only walk and push boxes. The warehouseman isn't strong enough to pull the boxes or push more than one box. The goal is to minimize the pushes and steps and to find the best solution possible for each level. In the original there are 50 Levels. 

In this version there will be no more than three levels but you can create your own by just adding new level files in pure ASCII-format inside the folder: /build/res/level/.

All the used assets were screenshotted from the internet and are used as dummy assets for development only. (Links below) In the future its planned to create self-made pixelgraphics.

## Manually actions
(August 3rd,2022) 
1. At the moment you only can make use of the first level-file "/res/level_1"). If you want to start the game from a different levelfile you need to adjust the variable currentLevel Game.h
2. before starting you need to copy the whole /res/ - folder to your build folder.

## Control

Move around with the cursor arrow-keys from your keyboard. At the moment no other input devices are supported.
With 'q' you can quit the game.

## Known issues
### Critical
Sometimes the renderer looses the connection and tzhe game crashes. Need to investigate.

### Logical
1. If the warehouse man pushes the same box over the goal over and over again the goal-counter increases and you can win the game with just won box. Need to investigate!
2. Sometimes the goal-texture will be removed when walking over it with a box.

## File structure

The source files are in the /src/-folder and the project is divided into several classes. Each class holds a different type of methods and datastructures. The ressource files needed (assets,levelstructure) live inside the /res - folder and should be copied to /build/res after building the project. 

The projects uses cmake and make to make building easier.

## Class structure

The project is divided into several classes. Each class has its own purpose. 
1. Controller - handles all the input of the user
2. Game - is the main class which holds all information about the game, the game.loop and the win-condition. Only one level at a time can be active.
3. Hero - is the class of the avatar and holds player-specific data and actions
4. Level - blueprint and datastructure for all level-specific actions
5. Renderer - SDL-specific implementation to render all textures of the game
6. Texture - Datastructure for a game-texture

## Rubric points

The following rubrics should be met the following criterias by the current submission from August 3rd, 2022. The project will proceed after the submission.

### Loop, Functions, I/O (2/3)

The project demonstrates an understanding of C++ functions and control structures: yes
The project reads data from a file and process the data, or the program writes data to a file: yes
The project accepts user input and processes the input: not yet

### Object Oriented Programming (5/9)

The project uses Object Oriented Programming techniques.: yes
Classes use appropriate access specifiers for class members.: yes
Class constructors utilize member initialization lists.: not all
Classes abstract implementation details from their interfaces.: no
Classes encapsulate behavior.: yes
Classes follow an appropriate inheritance hierarchy.: yes
Overloaded functions allow the same function to operate on different parameters.: no
Derived class functions override virtual base class functions.: no
Templates generalize functions in the project.: not yet

### Memory Management (3/6)

The project makes use of references in function declarations.: yes
The project uses destructors appropriately. kind of 
The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.: yes
The project follows the Rule of 5.: not yet
The project uses move semantics to move data, instead of copying it, where possible.: no
The project uses smart pointers instead of raw pointers.: yes

### Concurrency (0/4)

... will be implemented in the future.

The project uses multithreading.: no
A promise and future is used in the project.: no
A mutex or lock is used in the project.: no
A condition variable is used in the project.: no


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

## Libraries used
* SDL-ttf
  * This project makes use of [SDL_ttf](https://github.com/libsdl-org/SDL_ttf) 

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Copy folder /res to /build: ../build: cp -r ../res .
4. Run it: `./Zokoban`.

## Ressources / Links

[SDL tutorials](https://www.willusher.io/pages/sdl2/)
[SDL library](https://wiki.libsdl.org/)
[Sokoban levels](http://borgar.net/programs/sokoban/#Sokoban)
[SDL Keys](https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html)
[Story behind Sokoban](http://www.games4brains.de/sokoban-geschichte.php)
[used dummy graphic 1](https://www.shutterstock.com/image-vector/pixel-art-different-crates-set-detailed-1234507984)
[used dummy graphic 2](http://www.games4brains.de/sokoban-geschichte.php)

## Planned:
Game Requirements

DONE:

- walk u,d,l,r
- create levels from input files (ASCII based)
- push boxes
- goal area
- block playermovement if to many boxes or a wall
- win condition

TODO:
- basic Ui (menu start,end,options, select level))
- enter name and use it through the game for avatar
- some self drawn pixelart assets (first dummy assets)
-> cp assets to the build folder ! / create build/assets folder ...
- input name or level to load at beginning (The project accepts input from a user as part of the necessary operation of the program.)
- if boxes are blocked show hint that solving is impossible 
-> restart level
- All class members that are set to argument values are initialized through member initialization lists.
- use simple sounds
- show time needed
- show boxes left
- show movecounter, pushcounter updates 
- when level finished show results (resultscreen)
- (concurrencytask)- opponent ("cpu-ai") solving the same puzzle using pathfinding (A*) running in seperate thread / steals boxes & put them in other random places? -> need to solve the puzzle before opponent steals a box / one need jail the opponent with other boxes so stealing is not possible --> then solve the puzzle



## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
