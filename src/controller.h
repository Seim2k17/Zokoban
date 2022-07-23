#pragma once

#include "hero.h"

class Controller {
 public:
  void HandleInput(bool &running, Hero &hero) const;

 private:
  void ChangeDirection(Hero &hero, Hero::Direction input,
                       Hero::Direction opposite) const;
};