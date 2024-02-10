#include "SDL2/include/SDL.h"
#include "SDL2_ttf/include/SDL_ttf.h"
#include "SDL2_image/include/SDL_image.h"

#include "misc.h"

#pragma once

#define MAX_ENTITIES 255

/**
 * \brief This struct contains the width and height of an entity
*/
typedef struct Size2D {
  int width;
  int height;
} Size2D;

/**
 * \brief This struct takes place of an entity in the game
*/
typedef struct Entity {
  SDL_Rect rect;
  SDL_Texture* texture;
} Entity;

/**
 * \brief This struct contains the SDL_Window and SDL_Renderer pointers, as well as a boolean to check if the game is running
*/
typedef struct SDL_Instance {
  SDL_Window* window;
  SDL_Renderer* renderer;
  Size2D window_size;
  Entity entities[MAX_ENTITIES];
  int entity_count;

  bool running;
} SDL_Instance;

/**
 * \brief Initializes the SDL_Instance struct
 *
 * \return The initialized SDL_Instance struct
*/
struct SDL_Instance game_new(void) {
  struct SDL_Instance instance;
  instance.running = true;
  instance.window_size.width = 800;  //! TODO: Magic numbers, must change.
  instance.window_size.height = 600;  //! TODO: Magic numbers, must change.

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    perrorf("Could not initialize SDL: %s\n", SDL_GetError());
    instance.running = false;
    return instance;
  }

  instance.window = SDL_CreateWindow(
    "SDL2 Window",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    instance.window_size.width, instance.window_size.height,
    0
  );

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

  // Create entities
  SDL_Surface* tmp = IMG_Load("..\\assets\\player.png");
  if (tmp == NULL) {
    perrorf("Could not load texture: %s\n", SDL_GetError());
    instance.running = false;
    return instance;
  }
  instance.entity_count += 1;

  instance.entities[instance.entity_count].texture = SDL_CreateTextureFromSurface(instance.renderer, tmp);
  SDL_FreeSurface(tmp);

  instance.entities[instance.entity_count].rect.x = 0;
  instance.entities[instance.entity_count].rect.y = 0;
  instance.entities[instance.entity_count].rect.w = 32;
  instance.entities[instance.entity_count].rect.h = 32;

  SDL_SetRenderDrawColor(instance.renderer, 90, 90, 90, 255);
  SDL_RenderClear(instance.renderer);

  return instance;
}

/**
 * \brief Frees the memory allocated for the SDL_Instance struct
 *
 * \param instance The SDL_Instance struct to free
 * \return void
 * \note This function should be called at the end of the program
*/
void game_free(struct SDL_Instance* instance) {
  SDL_DestroyRenderer(instance->renderer);
  SDL_DestroyWindow(instance->window);
  SDL_Quit();
  return;
}

/**
 * \brief Handles SDL events
 *
 * \param instance The SDL_Instance struct to handle events for
 * \return void
*/
void game_handleEvents(struct SDL_Instance* instance) {
  SDL_Event event;
  // float frame_time = 1.0 / 60.0;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      instance->running = false;
      break;
    case SDL_KEYDOWN: {
      switch (event.key.keysym.sym) {

        // Quit
        case SDLK_ESCAPE:
        case SDLK_q:
          instance->running = false;
          break;

        case SDLK_w:
          instance->entities[0].rect.y -= 1;
          printf("Y: %d\n", instance->entities[0].rect.y);
          break;
        case SDLK_a:
          instance->entities[0].rect.x -= 1;
          printf("X: %d\n", instance->entities[0].rect.x);
          break;
        case SDLK_s:
          instance->entities[0].rect.y += 1;
          printf("Y: %d\n", instance->entities[0].rect.y);
          break;
        case SDLK_d:
          instance->entities[0].rect.x += 1;
          printf("X: %d\n", instance->entities[0].rect.x);
          break;

        default:
          break;
      }
    }
    default:
      break;
  }
  return;
}

/**
 * \brief Updates the game state. This function should update game logic and other required data
 *
 * \param instance The SDL_Instance struct to update the game state for
 * \return void
*/
void game_update(struct SDL_Instance* instance) {
  // Check for collisions

  for (int i = 0; i < instance->entity_count; i++) {
    // Out of bounds check

    if ((instance->entities[i].rect.x + instance->entities[i].rect.w) < instance->window_size.width) {
      instance->entities[i].rect.x = instance->window_size.width - instance->entities[i].rect.w;
    }
    if ((instance->entities[i].rect.y + instance->entities[i].rect.h) < instance->window_size.height) {
      instance->entities[i].rect.y = instance->window_size.height - instance->entities[i].rect.h;
    }

    if (instance->entities[i].rect.x < 0) {
      instance->entities[i].rect.x = 0;
    }
    if (instance->entities[i].rect.y < 0) {
      instance->entities[i].rect.y = 0;
    }
  }

  return;
}

/**
 * \brief Updates the game's display. This function should render the game based on game data
 *
 * \param instance The SDL_Instance struct to render the game for
 * \return void
*/
void game_render(struct SDL_Instance* instance) {
  SDL_RenderClear(instance->renderer);

  for (int i = 0; i < instance->entity_count; i++) {
    SDL_RenderCopy(instance->renderer, instance->entities[instance->entity_count].texture, NULL, &instance->entities[instance->entity_count].rect);
  }

  // Game void
  SDL_SetRenderDrawColor(instance->renderer, 90, 90, 90, 255);

  SDL_RenderPresent(instance->renderer);
  return;
}