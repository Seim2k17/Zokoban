#pragma once

#include "hero.h"
#include "level.h"

#include <vector>
#include <string>
#include <memory>
#include "SDL.h"


class SDL_Rect;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, const std::string_view& version);
  ~Renderer();

  void Render(Hero& hero, std::unique_ptr<Level>& level);
  void RenderTexture(const std::string& texturePath, const SDL_Rect& source, const SDL_Rect& destination);
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