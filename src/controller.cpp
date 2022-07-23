#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "hero.h"

void Controller::ChangeDirection(Hero &hero, Hero::Direction input,
                                 Hero::Direction opposite) const {
  //if (hero.direction != opposite || hero.size == 1) hero.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Hero &hero) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(hero, Hero::Direction::kUp,
                          Hero::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(hero, Hero::Direction::kDown,
                          Hero::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(hero, Hero::Direction::kLeft,
                          Hero::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(hero, Hero::Direction::kRight,
                          Hero::Direction::kLeft);
          break;
      }
    }
  }
}