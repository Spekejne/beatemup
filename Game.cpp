#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "Combat.h"
#include "Render.h"
#include "level.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int running = 1;
GameState gameState = STATE_MENU;

Player player;
Enemy enemies[16];
int enemyCount = 0;

bool initGame() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;

    SDL_Surface* surface = SDL_LoadBMP("background.bmp");
    if (!surface) {
    printf("Nie mozna zaladowac background.bmp: %s\n", SDL_GetError());
    return false;
    }


    background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);


    if (!background) {
    printf("Nie mozna utworzyc tekstury tla: %s\n", SDL_GetError());
    return false;
    }

    window = SDL_CreateWindow("Beat'em Up",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800, 600, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    initPlayer(&player);
    loadLevel("level.txt", enemies, &enemyCount);

    return true;
}

void shutdownGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void gameLoop() {
    Uint32 last = SDL_GetTicks();

    while (running) {
        Uint32 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        handleInput(&player);

        if (gameState == STATE_GAME) {
            updatePlayer(&player, dt);

            for (int i = 0; i < enemyCount; i++)
                updateEnemy(&enemies[i], &player, dt);

            handleCombat(&player, enemies, enemyCount);
        }

        renderFrame(&player, enemies, enemyCount);
        SDL_Delay(16);
    }
}


