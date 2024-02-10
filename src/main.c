#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED

#include "../lib/misc.h"
#include "../lib/game.h"

int main(int argc, char* argv[]) {
  struct SDL_Instance sdl = game_new();

  while (sdl.running) {
    game_handleEvents(&sdl);
    game_update(&sdl);
    game_render(&sdl);
  }

  game_free(&sdl);
  return 0;
}