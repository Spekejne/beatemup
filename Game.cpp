#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "Combat.h"
#include "Render.h"
#include "level.h"
#include "Collision.h"

SDL_Texture* background = nullptr;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int running = 1;
GameState gameState = STATE_MENU;

Player player;
Enemy enemies[16];
int enemyCount = 0;
int currentLevel;

// 🔥 FLAGA PRZEJŚCIA LEVELU
bool levelTransition = false;

bool initGame() {
if (SDL_Init(SDL_INIT_VIDEO) != 0) {
printf("SDL init error: %s\n", SDL_GetError());
return false;
}

// 1️⃣ OKNO
window = SDL_CreateWindow(
"Beat'em Up",
SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
800, 600, 0
);

if (!window) {
printf("Window error: %s\n", SDL_GetError());
return false;
}

// 2️⃣ RENDERER
renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
if (!renderer) {
printf("Renderer error: %s\n", SDL_GetError());
return false;
}

// 3️⃣ TŁO
char* basePath = SDL_GetBasePath();
char path[512];
snprintf(path, sizeof(path), "%sbackground.bmp", basePath);
SDL_free(basePath);

SDL_Surface* surface = SDL_LoadBMP(path);
if (!surface) {
printf("BMP load error: %s\n", SDL_GetError());
return false;
}

background = SDL_CreateTextureFromSurface(renderer, surface);
SDL_FreeSurface(surface);

if (!background) {
printf("Texture error: %s\n", SDL_GetError());
return false;
}

initPlayer(&player);

// START LEVEL 1 od razu
startLevel(1);

gameState = STATE_GAME;
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
// 1️⃣ UPDATE LOGIKI GRACZA
updatePlayer(&player, dt);
updatePlayerHitboxes(&player);

// 2️⃣ UPDATE ENEMY
for (int i = 0; i < enemyCount; i++) {
updateEnemy(&enemies[i], &player, dt);
updateEnemyHitboxes(&enemies[i]);
}

// 3️⃣ BODY COLLISION
for (int i = 0; i < enemyCount; i++) {
if (!enemies[i].alive) continue;
resolveBodyCollision(&player, &enemies[i]);
}

// 4️⃣ WALKA
handleCombat(&player, enemies, enemyCount);

// 5️⃣ SPRAWDŹ KONIEC LEVELU
bool allEnemiesDead = true;
for (int i = 0; i < enemyCount; i++) {
if (enemies[i].alive) {
allEnemiesDead = false;
break;
}
}

if (allEnemiesDead && !levelTransition) {
levelTransition = true;

if (currentLevel == 1) {
startLevel(2);
} else {
gameState = STATE_MENU; // koniec gry albo wróć do menu
}
}
}

// 6️⃣ RENDER
renderFrame(&player, enemies, enemyCount);

// MAŁE OPÓŹNIENIE ~60FPS
SDL_Delay(16);
}
}


