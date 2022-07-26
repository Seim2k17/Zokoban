#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "hero.h"

void Controller::SetDirection(Hero &hero, Hero::Direction input) const {
  //if (hero.direction != opposite || hero.size == 1) hero.direction = input;
  switch (input)
  {
    case Hero::Direction::kUp:
      hero.setPosition(0,-1);
      break;
    case Hero::Direction::kDown:
      hero.setPosition(0,1);
      break;
    case Hero::Direction::kLeft:
      hero.setPosition(-1,0);
      break;
    case Hero::Direction::kRight:
      hero.setPosition(1,0);
      break;    
    default:
      break;
  }
}

void Controller::HandleInput(bool &running, Hero &hero) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          SetDirection(hero, Hero::Direction::kUp);
          break;
        case SDLK_DOWN:
          SetDirection(hero, Hero::Direction::kDown);
          break;

        case SDLK_LEFT:
          SetDirection(hero, Hero::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          SetDirection(hero, Hero::Direction::kRight);
          break;
        case SDLK_q:
          std::cout << "q pressed" << std::endl;
          running = false;
          return;
        default:
          std::cout << "key pressed: " << e.key.keysym.sym << std::endl;
      }
    }
  }
}