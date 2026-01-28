#include "Render.h"
#include "Game.h"

void renderFrame(Player* p, Enemy* e, int count) {
    SDL_RenderClear(renderer);

    // 🔹 TŁO
    SDL_Rect bg = { 0, 0, 800, 600 };
    SDL_RenderCopy(renderer, background, NULL, &bg);

    // 🔹 GRACZ
    if (p->action == ACT_ATTACK)
        drawAnimation(&p->attack, p->x, p->y - p->z, p->facing);
    else if (p->action == ACT_WALK)
        drawAnimation(&p->walk, p->x, p->y - p->z, p->facing);
    else
        drawAnimation(&p->idle, p->x, p->y - p->z, p->facing);

    // 🔹 WROGOWIE
    for (int i = 0; i < count; i++) {
    if (!e[i].alive) continue;

    if (e[i].action == EN_WALK)
        drawAnimation(&e[i].walk, e[i].x, e[i].y, e[i].facing);
    else
        drawAnimation(&e[i].idle, e[i].x, e[i].y, e[i].facing);
}

    SDL_RenderPresent(renderer);
}

