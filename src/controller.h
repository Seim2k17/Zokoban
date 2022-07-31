#pragma once
#include <memory>

#include "hero.h"


class Level;

class Controller {
 public:
  void HandleInput(bool &running, Hero &hero, std::unique_ptr<Level>& level) const;

 private:
  void SetDirection(Hero &hero, Hero::Direction input, std::unique_ptr<Level>& level) const;
  void SetDirectionInput(int x, int y) const;

};