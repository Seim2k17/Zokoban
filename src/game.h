#pragma once

#include <random>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "hero.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::string name);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  

 private:
  Hero hero;
  //SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int currentLevel{1};

  void CreateLevel(int level);
  void Update();
};