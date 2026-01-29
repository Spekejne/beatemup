#include "Input.h"
#include "Game.h"
#include <SDL.h>

void handleInput(Player* p) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = 0;
    }

    const Uint8* k = SDL_GetKeyboardState(nullptr);

    if (gameState == STATE_MENU) {
    const Uint8* k = SDL_GetKeyboardState(nullptr);

    if (k[SDL_SCANCODE_N]) {
        gameState = STATE_GAME;
        startLevel(1);
    }
        return;
    }

    if (k[SDL_SCANCODE_Q]) {
        gameState = STATE_GAME;
    }

    // --- RUCH ---
    p->vx = 0;

    if (k[SDL_SCANCODE_A]) {
        p->vx = -200;
        p->facing = -1;
    }
    else if (k[SDL_SCANCODE_D]) {
        p->vx = 200;
        p->facing = 1;
    }

    if (k[SDL_SCANCODE_SPACE] && p->z == 0) {
        p->vz = 20;
    }

    // --- ATAK (EDGE TRIGGER) ---
    static int prevX = 0;
    int currX = k[SDL_SCANCODE_X];

    if (currX && !prevX && p->action != ACT_ATTACK) {
        p->action = ACT_ATTACK;
        p->attack.frame = 0;
        p->attack.timer = 0;
    }

    prevX = currX;
}










