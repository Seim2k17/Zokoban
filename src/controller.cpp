#include "controller.h"
#include <iostream>
#include <memory>

#include "SDL.h"
#include "hero.h"
#include "level.h"

void Controller::SetDirection(Hero &hero, Hero::Direction input, std::unique_ptr<Level>& level) const {
  
  std::pair<int,int> direction;
  switch (input)
  {
    case Hero::Direction::kUp:
      direction = {-1,0};
      break;
    case Hero::Direction::kDown:
      direction = {1,0};
      break;
    case Hero::Direction::kLeft:
      direction = {0,-1};
      break;
    case Hero::Direction::kRight:
      direction = {0,1};
      break;    
    default:
      break;
  }
   
  PossiblePush push = hero.changeHeroTexturePosition(direction.first,direction.second,level);
  level->setPlayerPosition(hero.getCurrentHeroCellPosition(), hero.getLastHeroCellPosition(),direction,push.pushingPossible);

  if(push.pushingPossible && level->getLevelData()[push.potentialRow][push.potentialCol].texture.type == TextureType::Box)
  {
    level->changeBoxPosition(push.potentialRow, push.potentialCol,direction);
  }
  
  level->setCurrentDirectionInput(direction);
  

}

void Controller::HandleInput(bool &running, Hero &hero, std::unique_ptr<Level>& level) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          SetDirection(hero, Hero::Direction::kUp, level);
          break;
        case SDLK_DOWN:
          SetDirection(hero, Hero::Direction::kDown, level);
          break;
        case SDLK_LEFT:
          SetDirection(hero, Hero::Direction::kLeft, level);
          break;
        case SDLK_RIGHT:
          SetDirection(hero, Hero::Direction::kRight, level);
          break;
        case SDLK_q:
          std::cout << "q pressed" << std::endl;
          running = false;
          return;
        default:
          std::cout << "key pressed: " << e.key.keysym.sym << std::endl;
      }
    } else if (e.type == SDL_KEYUP) /// reset at release arrowkeys
      {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_LEFT:
        case SDLK_RIGHT:
          level->setCurrentDirectionInput({0,0});
          break;
        }
      }
  }
}