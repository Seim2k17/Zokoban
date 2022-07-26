#pragma once

#include "hero.h"

class Controller {
 public:
  void HandleInput(bool &running, Hero &hero) const;

 private:
  void SetDirection(Hero &hero, Hero::Direction input) const;
};