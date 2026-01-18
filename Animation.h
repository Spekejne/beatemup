#pragma once
#include <SDL.h>

#include <SDL2/SDL_render.h>

struct Animation {
    SDL_Texture* tex;
    int frames;
    int w, h;
    float time, timer;
    int frame;
};

void initAnimation(Animation* a, SDL_Renderer* r,
                   const char* path, int f, int w, int h, float t);
void updateAnimation(Animation* a, float dt);
void drawAnimation(Animation* a, int x, int y, int flip);

