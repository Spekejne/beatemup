#include "Input.h"
#include "Game.h"
#include <SDL.h>

void handleInput(Player* p) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) running = 0;
    }

    const Uint8* k = SDL_GetKeyboardState(nullptr);
    p->vx = 0;
    p->action = ACT_IDLE;

    if (k[SDL_SCANCODE_A]) { p->vx = -200; p->facing = -1; p->action = ACT_WALK; }
    if (k[SDL_SCANCODE_D]) { p->vx = 200;  p->facing = 1;  p->action = ACT_WALK; }

    if (k[SDL_SCANCODE_SPACE] && p->z == 0) {
        p->vz = 20;
        p->action = ACT_JUMP;
    }

    if (k[SDL_SCANCODE_X]) {
        p->action = ACT_ATTACK;
        p->combo.pushInput(IN_X, SDL_GetTicks());
    }
}

