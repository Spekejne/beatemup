#include "Render.h"
#include "Game.h"

void renderFrame(Player* p, Enemy* e, int count) {
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    drawAnimation(&p->idle, p->x, p->y - p->z, p->facing);

    for (int i = 0; i < count; i++)
        if (e[i].alive)
            drawAnimation(&e[i].idle, e[i].x, e[i].y, 1);

    SDL_RenderPresent(renderer);
}
