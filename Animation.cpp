#include "Animation.h"
#include "Game.h"   // żeby mieć dostęp do globalnego renderer

void initAnimation(Animation* a, SDL_Renderer* r,
                   const char* path, int f, int w, int h, float t, Uint8 rKey, Uint8 gKey, Uint8 bKey) {
    SDL_Surface* s = SDL_LoadBMP(path);
    if (!s) {
        printf("❌ FAILED TO LOAD %s: %s\n", path, SDL_GetError());
        a->tex = NULL;
        return;
    }

    // COLOR KEY (tło)
    Uint32 key = SDL_MapRGB(s->format, rKey, gKey, bKey);
    SDL_SetColorKey(s, SDL_TRUE, key);

    a->tex = SDL_CreateTextureFromSurface(r, s);
    SDL_FreeSurface(s);

    if (!a->tex) {
        printf("❌ FAILED TO CREATE TEX %s: %s\n", path, SDL_GetError());
        return;
    }

    printf("✅ LOADED %s\n", path);

    a->frames = f;
    a->w = w;
    a->h = h;
    a->time = t;
    a->timer = 0;
    a->frame = 0;
}

void updateAnimation(Animation* a, float dt) {
    if (!a || a->frames <= 0) return;   // 🔥 KLUCZOWE

    a->timer += dt;
    if (a->timer >= a->time) {
        a->timer -= a->time;
        a->frame = (a->frame + 1) % a->frames;
    }
}

void drawAnimation(Animation* a, int x, int y, int flip, int scale) {
    if (!a || !a->tex) return;

    SDL_Rect src = { a->frame * a->w, 0, a->w, a->h };
    SDL_Rect dst = { x, y, a->w * scale, a->h * scale};

    SDL_RenderCopyEx(
        renderer,              // ✅ TEN SAM renderer
        a->tex,
        &src,
        &dst,
        0,
        nullptr,
        flip == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );
}









