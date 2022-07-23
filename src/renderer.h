#pragma once

#include "hero.h"

#include <vector>
#include <string_view>
#include "SDL.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, const std::string_view& version);
  ~Renderer();

  void Render(Hero const hero /*, SDL_Point const &food*/);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  const std::string_view game_version;
};