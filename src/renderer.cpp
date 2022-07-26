#include "renderer.h"
// TODO: check solution
// error checks but problems with multiple definition when using make
//#include "resource_path.h"

#include "hero.h"
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <SDL.h>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height,
                   const std::string_view& version)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      game_version(version) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  const char* gameVersion = (std::string("Zokoban ") + std::string(game_version)).c_str();
  
  sdl_window = SDL_CreateWindow(gameVersion, SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::RenderTexture(const std::string& texturePath, const SDL_Rect& source, const SDL_Rect& destination)
{
  // load image
  SDL_Surface* bmp = SDL_LoadBMP(texturePath.c_str());
  if (bmp == nullptr)
  {
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    std::cout << "BMP Error" << SDL_GetError() << std::endl;
    SDL_Quit();
    return;
  }

  // create texture for renderer
  SDL_Texture* tex = SDL_CreateTextureFromSurface(sdl_renderer, bmp);
  SDL_FreeSurface(bmp);
  if(tex == nullptr)
  {
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    std::cout << "CreateTeture Error" << SDL_GetError() << std::endl;
    SDL_Quit();
    return;
  }

	//Draw the texture
	SDL_RenderCopy(sdl_renderer, tex, &source, &destination);
}

void Renderer::Render(Hero& hero, std::unique_ptr<Level>& level) {
  /*
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  */


  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  TextureData heroData = hero.getTextureData();

  // render hero texture
  RenderTexture(heroData.texturePath, heroData.Source, heroData.Destination);
  
	//Update the screen
	SDL_RenderPresent(sdl_renderer);
	
}


void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{std::string("Zokoban ") + std::string(game_version) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
