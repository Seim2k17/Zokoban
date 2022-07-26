#include "controller.h"
#include "game.h"
#include "renderer.h"

#include <string_view>
#include <iostream>

// TODO: increase game version
constexpr std::string_view gameVersion{"v.0.1"};



int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, gameVersion);
  Controller controller;
  Game game(kGridWidth, kGridHeight, "STANDARD");
  game.Run(controller, renderer, kMsPerFrame);
  
  std::cout << "Game has terminated successfully!\n";
  
  return 0;
}