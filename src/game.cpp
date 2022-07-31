#include "game.h"
#include "level.h"

#include <iostream>
#include <string>
#include <memory>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, std::string name)
    : hero(grid_width, grid_height, name),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  
  std::cout << "Run started " << std::endl;
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  CreateLevel(currentLevel);
   
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, hero, _level);
    Update();
    // unique ptrs can't be copied -> we need to move the ownership -> but then dtor will be called / so we pass it by reference tro use the ressource 
    renderer.Render(hero, _level);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }


  }
}

void Game::CreateLevel(int level) {
  std::cout << "create Level: " << level << std::endl;
  _level = std::make_unique<Level>(level);
}

void Game::Update() {
  
  hero.Update(_level.get()->getLevelData());
  _level.get()->Update(hero.getCurrentHeroCellPosition(), hero.getLastHeroCellPosition());
   
  /*
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    CreateLevel();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  */
}