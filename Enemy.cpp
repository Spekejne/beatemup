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

    // 💀 ŚMIERĆ
    if (e->action == EN_DEAD) {
        updateAnimation(&e->dead, dt);
        return;
    }

    // 💥 HIT
    if (e->action == EN_HIT) {
        updateAnimation(&e->hit, dt);
        if (e->hit.frame == e->hit.frames - 1) {
            if (e->hp <= 0) {
                e->action = EN_DEAD;
            } else {
                e->action = EN_IDLE;
            }
            e->hit.frame = 0;
            e->hit.timer = 0;
        }
        return;
    }

    float dx = p->x - e->x;

    // ⚔️ ATAK
    if (fabs(dx) < 40) {
        e->vx = 0;
        e->action = EN_ATTACK;
        updateAnimation(&e->attack, dt);

        // HIT PLAYERA (prosto)
        if (e->attack.frame == 2) {
            p->hp -= 1;
        }

        if (e->attack.frame == e->attack.frames - 1) {
            e->attack.frame = 0;
            e->attack.timer = 0;
            e->action = EN_IDLE;
        }
        return;
    }

    // 🚶 CHODZENIE
    if (fabs(dx) > 5) {
        e->vx = (dx > 0) ? 60 : -60;
        e->facing = (dx > 0) ? 1 : -1;
        e->action = EN_WALK;
    } else {
        e->vx = 0;
        e->action = EN_IDLE;
    }

    e->x += e->vx * dt;

    if (e->action == EN_WALK)
        updateAnimation(&e->walk, dt);
    else
        updateAnimation(&e->idle, dt);
}


