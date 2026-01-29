#include "Enemy.h"
#include "Player.h"
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

    // ⚠️ DOPASUJ ŚCIEŻKI I ROZMIARY DO SWOICH BMP
    initAnimation(&e->idle,   renderer, "enemy_idle.bmp",   5, 64, 64, 0.15f, 255, 0, 255);
    initAnimation(&e->walk,   renderer, "enemy_walk.bmp",   5, 64, 64, 0.10f, 255, 0, 255);
    //initAnimation(&e->attack, renderer, "assets/enemy_attack.bmp", 5, 64, 64, 0.10f);
    //initAnimation(&e->hit,    renderer, "assets/enemy_hit.bmp",    2, 64, 64, 0.15f);
    //initAnimation(&e->dead,   renderer, "assets/enemy_dead.bmp",   5, 64, 64, 0.20f);
}

void updateEnemyHitboxes(Enemy* e) {
    int spriteW = e->idle.w * SCALE;
    int spriteH = e->idle.h * SCALE;

    e->hurtbox.x = e->x + spriteW * 0.25f;
    e->hurtbox.y = e->y + spriteH * 0.2f;
    e->hurtbox.w = spriteW * 0.5f;
    e->hurtbox.h = spriteH * 0.7f;

    if (e->action == EN_ATTACK) {
        int dir = e->facing;
        e->hitbox.w = spriteW * 0.4f;
        e->hitbox.h = spriteH * 0.3f;
        e->hitbox.x = e->x + (dir == 1 ? spriteW : -e->hitbox.w);
        e->hitbox.y = e->y + spriteH * 0.35f;
    } else {
        e->hitbox.w = 0;
        e->hitbox.h = 0;
    }
}

void updateEnemy(Enemy* e, Player* p, float dt) {
    updateEnemyHitboxes(e);
    // 💀 ŚMIERĆ – animuje się, a dopiero potem znika
    if (e->action == EN_DEAD) {
        updateAnimation(&e->dead, dt);
        if (e->dead.frame == e->dead.frames - 1) {
            e->alive = 0;   // zniknie po animacji
        }
        return;
    }

    // ❌ jeśli już martwy (po animacji) – nic nie rób
    if (!e->alive)
        return;

    // 💥 HIT
    if (e->action == EN_HIT) {
        updateAnimation(&e->hit, dt);
        if (e->hit.frame == e->hit.frames - 1) {
            if (e->hp <= 0) {
                e->action = EN_DEAD;
                e->dead.frame = 0;
                e->dead.timer = 0;
            } else {
                e->action = EN_IDLE;
            }
            e->hit.frame = 0;
            e->hit.timer = 0;
        }
        return;
    }

    float dx = p->x - e->x;

    // ⚔️ ATAK (gdy blisko gracza)
    if (fabs(dx) < 40) {
        e->vx = 0;
        e->action = EN_ATTACK;
        updateAnimation(&e->attack, dt);

        // przykładowy hit gracza w konkretnej klatce
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

    // 🚶 CHODZENIE DO GRACZA
    if (fabs(dx) > 5) {
        e->vx = (dx > 0) ? 60.0f : -60.0f;
        e->facing = (dx > 0) ? 1 : -1;
        e->action = EN_WALK;
    } else {
        e->vx = 0;
        e->action = EN_IDLE;
    }

    e->x += e->vx * dt;

    // 🎞️ Animacje
    if (e->action == EN_WALK)
        updateAnimation(&e->walk, dt);
    else
        updateAnimation(&e->idle, dt);
}

