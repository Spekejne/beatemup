#include "Enemy.h"
#include "Game.h"
#include <cmath>


void initEnemy(Enemy* e, float x, float y) {
e->x = x;
e->y = y;
e->vx = 0;
e->facing = -1;
e->alive = 1;
e->hp = 3;
e->action = EN_IDLE;


initAnimation(&e->idle, renderer, "enemy_idle.bmp", 4, 24, 32, 0.2f);
initAnimation(&e->walk, renderer, "enemy_walk.bmp", 6, 24, 32, 0.1f);
initAnimation(&e->attack, renderer, "enemy_attack.bmp", 4, 32, 32, 0.1f);
initAnimation(&e->hit, renderer, "enemy_hit.bmp", 2, 24, 32, 0.15f);
initAnimation(&e->dead, renderer, "enemy_dead.bmp", 4, 24, 32, 0.2f);
}

void updateEnemy(Enemy* e, Player* p, float dt) {
if (!e->alive) return;


float dx = p->x - e->x;


if (fabs(dx) > 5) {
e->vx = (dx > 0) ? 80 : -80;
e->facing = (dx > 0) ? 1 : -1;
e->action = EN_WALK;
} else {
e->vx = 0;
e->action = EN_IDLE;
}


e->x += e->vx * dt;


// 🔹 animacje
if (e->action == EN_WALK)
updateAnimation(&e->walk, dt);
else
updateAnimation(&e->idle, dt);
}

