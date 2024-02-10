#include "SDL2/include/SDL.h"
#include "SDL2_ttf/include/SDL_ttf.h"

#include "misc.h"

#pragma once

typedef struct SDL_Instance {
  SDL_Window* window;
  SDL_Renderer* renderer;
  bool running;
} SDL_Instance;

struct SDL_Instance game_new(void) {
  struct SDL_Instance instance = {NULL, NULL, true};

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    perrorf("Could not initialize SDL: %s\n", SDL_GetError());
    instance.running = false;
    return instance;
  }

  instance.window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);  //! TODO: magic numbers, change later

  if (instance.window == NULL) {
    perrorf("Could not create window: %s\n", SDL_GetError());
    instance.running = false;
    return instance;
  }

  instance.renderer = SDL_CreateRenderer(instance.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (instance.renderer == NULL) {
    perrorf("Could not create renderer: %s\n", SDL_GetError());
    instance.running = false;
    return instance;
  }

  SDL_Color off_gray = {100, 100, 100, 255};

  SDL_SetRenderDrawColor(instance.renderer, off_gray.r, off_gray.g, off_gray.b, off_gray.a);  //! TODO: magic numbers, change later

  return instance;
}

void game_free(struct SDL_Instance* instance) {
  SDL_DestroyRenderer(instance->renderer);
  SDL_DestroyWindow(instance->window);
  SDL_Quit();
  return;
}

void game_handleEvents(struct SDL_Instance* instance) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      instance->running = false;
      break;
    case SDL_KEYDOWN: {
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          instance->running = false;
          break;
      }
    }
  }
  return;
}

void game_update(struct SDL_Instance* instance) {
  return;
}

void game_render(struct SDL_Instance* instance) {
  SDL_RenderClear(instance->renderer);
  SDL_RenderPresent(instance->renderer);
  return;
}