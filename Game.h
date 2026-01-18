#pragma once
#include <SDL2/SDL.h>
#include "State.h"
#include "sdl/include/SDL2/SDL_render.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int running;
extern GameState gameState;

bool initGame();
void shutdownGame();
void gameLoop();
