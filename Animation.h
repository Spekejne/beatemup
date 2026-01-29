#pragma once
#include <SDL2/SDL.h>

struct Animation {
    SDL_Texture* tex;
    int frames;
    int w, h;
    float time, timer;
    int frame;
    Uint8 rKey, Uint8 gKey, Uint8 bKey;
};

void initAnimation(Animation* a, SDL_Renderer* r,
                   const char* path, int f, int w, int h, float t);
void updateAnimation(Animation* a, float dt);
void drawAnimation(Animation* a, int x, int y, int flip, int scale;);



