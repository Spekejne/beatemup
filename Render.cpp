#include "Render.h"
#include "Game.h"

void renderFrame(Player* p, Enemy* e, int count) {
    if (gameState == STATE_MENU) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return;
}
    
    // 🎨 WYCZYŚĆ EKRAN
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 🖼️ TŁO (ZAWSZE PIERWSZE)
    if (background) {
        SDL_Rect bg = { 0, 0, 800, 600 };
        SDL_RenderCopy(renderer, background, NULL, &bg);
    }

    // 🧍 GRACZ
    if (p->action == ACT_ATTACK)
        drawAnimation(&p->attack, p->x, p->y - p->z, p->facing, 3);
    else if (p->action == ACT_WALK)
        drawAnimation(&p->walk, p->x, p->y - p->z, p->facing, 3);
    else
        drawAnimation(&p->idle, p->x, p->y - p->z, p->facing, 3);

    // 👾 ENEMY
    for (int i = 0; i < count; i++) {
        printf("RENDER enemy %d alive=%d x=%.1f y=%.1f\n",
           i, e[i].alive, e[i].x, e[i].y);
}
    for (int i = 0; i < count; i++) {
        if (!e[i].alive) continue;

        if (e[i].action == EN_ATTACK)
            drawAnimation(&e[i].attack, e[i].x, e[i].y, e[i].facing, 2);
        else if (e[i].action == EN_WALK)
            drawAnimation(&e[i].walk, e[i].x, e[i].y, e[i].facing, 2);
        else
            drawAnimation(&e[i].idle, e[i].x, e[i].y, e[i].facing, 2);
    }

    // 🖥️ POKAŻ KLATKĘ
    SDL_RenderPresent(renderer);
}






