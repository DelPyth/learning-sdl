#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED

#include "../lib/SDL2/include/SDL.h"
#include "../lib/SDL2_ttf/include/SDL_ttf.h"

#include "../lib/misc.h"

void perrorf(char* msg, ...) {
  va_list args;
  va_start(args, msg);
  vfprintf(stderr, msg, args);
  va_end(args);
  return;
}

bool sdlStartup(struct SDL_Renderer* renderer, struct SDL_Window* window) {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("SDL2 Window",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      640, 640, 0);

  if (window == NULL) {
    perrorf("Could not create window: %s\n", SDL_GetError());
    return true;
  }

  renderer = SDL_CreateRenderer(window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == NULL) {
    perrorf("Could not create renderer: %s\n", SDL_GetError());
    return true;
  }

  return false;
}

int main(int argc, char* argv[]) {
  // Initialize SDL and create a window
  SDL_Renderer* renderer = NULL;
  SDL_Window* window = NULL;

  if (sdlStartup(renderer, window)) {
    return 1;
  }

  // Now we create a starting screen
  // TODO: ...


  SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);

  // Draw some text
  SDL_Color color = {255, 255, 255, 255};

  if (TTF_Init() == -1) {
    perrorf("TTF_Init: %s\n", TTF_GetError());
    return 1;
  }

  char font_path[1024];
  char* cwd = (char*)malloc(1024);
  if (!workingDir(cwd)) {
    perrorf("Could not set working directory\n");
    return 1;
  }
  sprintf(font_path, "%s\\assets\\ubuntu.ttf", cwd);

  TTF_Font* font = TTF_OpenFont(font_path, 24);
  if (font == NULL) {
    perrorf("TTF_OpenFont: %s\n", TTF_GetError());
    return 1;
  }

  SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, World!", color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_Rect textRect;
  textRect.x = 320 - surface->w / 2;
  textRect.y = 320 - surface->h / 2;
  textRect.w = surface->w;
  textRect.h = surface->h;

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, &textRect);
  SDL_RenderPresent(renderer);

  // SDL_RenderClear(renderer);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  bool running = true;
  SDL_Event event = {0};

  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: { running = false; }
        case SDL_KEYDOWN: {
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: { running = false; }
          }
        }
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}