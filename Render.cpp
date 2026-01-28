#include "Render.h"
#include "Game.h"

void renderFrame(Player* p, Enemy* e, int count) {
    SDL_RenderClear(renderer);

    // 🔹 TŁO
    SDL_Rect bg = { 0, 0, 800, 600 };
    SDL_RenderCopy(renderer, background, NULL, &bg);

    // 🔹 GRACZ
    drawAnimation(&p->idle, p->x, p->y - p->z, p->facing);

    // 🔹 WROGOWIE
    for (int i = 0; i < count; i++)
        if (e[i].alive)
            drawAnimation(&e[i].idle, e[i].x, e[i].y, 1);

    SDL_RenderPresent(renderer);
}
