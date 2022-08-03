#pragma once

#include <random>
#include <string>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "hero.h"

class Level;

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::string name);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  
  void checkWinCondition();

 private:
  Hero hero;
  //SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int currentLevel{2};
  bool winCondition{false};

  std::unique_ptr<Level> _level;

  void CreateLevel(int level);
  void Update();

};