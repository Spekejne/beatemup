#include "Animation.h"

void initAnimation(Animation* a, SDL_Renderer* r,
                   const char* path, int f, int w, int h, float t) {
    SDL_Surface* s = SDL_LoadBMP(path);
    a->tex = SDL_CreateTextureFromSurface(r, s);
    SDL_FreeSurface(s);
    a->frames = f; a->w = w; a->h = h; a->time = t;
    a->timer = 0; a->frame = 0;
}

void updateAnimation(Animation* a, float dt) {
    a->timer += dt;
    if (a->timer >= a->time) {
        a->timer = 0;
        a->frame = (a->frame + 1) % a->frames;
    }
}

void drawAnimation(Animation* a, int x, int y, int flip) {
    SDL_Rect src = { a->frame * a->w, 0, a->w, a->h };
    SDL_Rect dst = { x, y, a->w, a->h };
    SDL_RenderCopyEx(SDL_GetRenderer(SDL_GetWindowFromID(1)),
                     a->tex, &src, &dst, 0, NULL,
                     flip == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
