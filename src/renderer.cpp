#include "renderer.h"
#include "resource_path.h"

#include <iostream>
#include <string>
#include <string_view>
#include <SDL.h>

#define TEXTURE_SIZE 32

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

void Renderer::Render(Hero const hero /*, SDL_Point const &food*/) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // TODO: refactor destroy in lambda/method, other loading in methods
  // load hero image
  std::string texturePath = getResourcePath("hero") + "avatar.bmp";
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

  // draw texture
  //First clear the renderer
	SDL_RenderClear(sdl_renderer);
	//Draw the texture
  SDL_Rect Source;
  SDL_Rect Destination;

  Source.x = 0;
  Source.y = 0;
  Source.w = TEXTURE_SIZE;
  Source.h = TEXTURE_SIZE;

  Destination.x = screen_width/2;
  Destination.y = screen_height/2;
  Destination.w = TEXTURE_SIZE;
  Destination.h = TEXTURE_SIZE;

	SDL_RenderCopy(sdl_renderer, tex, &Source, &Destination);
	//Update the screen
	SDL_RenderPresent(sdl_renderer);
	
}


void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{std::string("Zokoban ") + std::string(game_version) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
