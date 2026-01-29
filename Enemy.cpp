#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <cmath>
#include "Combat.h"

void initEnemy(Enemy* e, float x, float y) {
    e->x = x;
    e->y = y;
    e->vx = 0;
    e->facing = -1;
    e->alive = 1;
    e->hp = 3;
    e->attackDamage = 1;
    e->action = EN_IDLE;

    // ⚠️ DOPASUJ ŚCIEŻKI I ROZMIARY DO SWOICH BMP
    initAnimation(&e->idle,   renderer, "enemy_idle.bmp",   5, 64, 64, 0.15f, 255, 0, 255);
    initAnimation(&e->walk,   renderer, "enemy_walk.bmp",   5, 64, 64, 0.10f, 255, 0, 255);
    initAnimation(&e->attack, renderer, "enemy_attack.bmp", 5, 64, 64, 0.10f, 255, 0, 255);
}

void updateEnemyHitboxes(Enemy* e) {

    //martwy - brak kolizji
    if (!e->alive) {
        e->hurtbox.w = 0;
        e->hurtbox.h = 0;
        e->hitbox.w = 0;
        e->hitbox.h = 0;
        return;
    }
        
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

    if (!e->alive)
        return;

    float dx = p->x - e->x;
    float dist = fabs(dx);

    e->facing = (dx > 0) ? 1 : -1;

    // ⚔️ ATAK – TYLKO BARDZO BLISKO
    if (dist < 28) {
        e->vx = 0;
        e->action = EN_ATTACK;
        updateAnimation(&e->attack, dt);
        return;
    }

    if (e->action == EN_ATTACK && intersects(e->hitbox, p->hurtbox)) {
    p->hp -= 1;        // enemy damage
    p->combo = 0;     // 💥 reset combo po dostaniu hita
    p->comboTimer = 0;

    printf("PLAYER HIT! HP=%d\n", p->hp);

    if (p->hp <= 0) {
        gameState = STATE_MENU; // albo GAME OVER
    }
}

    // 🚶 CHODZENIE DO GRACZA
    if (dist > 30) {
        e->vx = (dx > 0) ? 60.0f : -60.0f;
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










