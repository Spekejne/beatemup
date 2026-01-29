#include "Render.h"
#include "Game.h"

void renderFrame(Player* p, Enemy* e, int count) {
    void renderFrame(Player* p, Enemy* e, int count) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 🟢 TEST GRACZA
    SDL_Rect r = { (int)p->x, (int)p->y, 50, 50 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &r);

    SDL_RenderPresent(renderer);
}
}




