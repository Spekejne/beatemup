#include "Animation.h"
#include "Game.h"   // żeby mieć dostęp do globalnego renderer

void initAnimation(Animation* a, SDL_Renderer* r,
                   const char* path, int f, int w, int h, float t) {

    SDL_Surface* s = SDL_LoadBMP(path);
    if (!s) {
        printf("Nie mozna zaladowac %s: %s\n", path, SDL_GetError());
        return;
    }

    // BIAŁY KOLOR JAKO PRZEZROCZYSTY
    Uint32 white = SDL_MapRGB(s->format, 255, 255, 255);
    SDL_SetColorKey(s, SDL_TRUE, white);

    a->tex = SDL_CreateTextureFromSurface(r, s);
    SDL_FreeSurface(s);

    if (!a->tex) {
        printf("Nie mozna utworzyc tekstury animacji: %s\n", SDL_GetError());
        return;
    }

    a->frames = f;
    a->w = w;
    a->h = h;
    a->time = t;
    a->timer = 0;
    a->frame = 0;
}

void updateAnimation(Animation* a, float dt) {
    a->timer += dt;
    if (a->timer >= a->time) {
        a->timer = 0;
        a->frame = (a->frame + 1) % a->frames;
    }
}

void drawAnimation(Animation* a, int x, int y, int flip) {
    if (!a->tex) return;

    SDL_Rect src = { a->frame * a->w, 0, a->w, a->h };
    SDL_Rect dst = { x, y, a->w, a->h };

    SDL_RenderCopyEx(
        renderer,              // 🔥 TEN renderer, którego używa cała gra
        a->tex,
        &src,
        &dst,
        0,
        NULL,
        flip == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );
}
