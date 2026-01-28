#include "Enemy.h"
#include "Game.h"

void initEnemy(Enemy* e, float x, float y) {
    e->x = x;
    e->y = y;
    e->vx = 0;
    e->facing = -1;
    e->alive = 1;
    e->action = EN_IDLE;

    initAnimation(
        &e->idle,
        renderer,
        "enemy_idle.bmp",
        4,        // liczba klatek
        24, 32,
        0.15f
    );

    initAnimation(
        &e->walk,
        renderer,
        "enemy_walk.bmp",
        6,
        24, 32,
        0.1f
    );
}

