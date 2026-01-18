#include "Enemy.h"
#include "Game.h"

void initEnemy(Enemy* e) {
    e->y = 420;
    e->hp = 30;
    e->alive = 1;
    initAnimation(&e->idle, renderer, "assets/enemy_idle.bmp", 1, 64, 96, 0.5f);
}

void updateEnemy(Enemy* e, Player* p, float dt) {
    if (!e->alive) return;

    if (p->x < e->x) e->x -= 60 * dt;
    if (p->x > e->x) e->x += 60 * dt;

    updateAnimation(&e->idle, dt);
}
