#include "Player.h"
#include "Game.h"

#define GRAVITY 40.0f
#define FLOOR_Y 420

void initPlayer(Player* p) {
    p->x = 100;
    p->y = FLOOR_Y;
    p->z = 0;
    p->vx = 0;
    p->vz = 0;
    p->hp = 100;
    p->facing = 1;
    p->action = ACT_IDLE;

    p->invincible = false;
    p->invincibleTimer = 0.0f;

    p->combo = 0;
    p->comboTimer = 0.0f;
    p->baseDamage = 400;

    initCombo(&p->combo);

    initAnimation(
        &p->idle,
        renderer,
        "player_idle.bmp",
        6, // liczba klatek
        24, 32, // szerokość, wysokość klatki
        0.12f,
        255, 255, 255
    );
    initAnimation(
        &p->walk,
        renderer,
        "player_walk.bmp",
        6,        // liczba klatek
        24, 32,   // rozmiar klatki
        0.1f,      // trochę szybciej niż idle
        255, 255, 255
    );
    initAnimation(
        &p->attack,
        renderer,
        "player_attack.bmp",
        6,        // liczba klatek
        22, 32,
        0.08f,
        255, 255, 255
    );
}

void updatePlayerHitboxes(Player* p) {
    int spriteW = p->idle.w * SCALE;
    int spriteH = p->idle.h * SCALE;

    // 📦 hurtbox (ciało)
    p->hurtbox.x = p->x + spriteW * 0.25f;
    p->hurtbox.y = p->y - p->z + spriteH * 0.2f;
    p->hurtbox.w = spriteW * 0.5f;
    p->hurtbox.h = spriteH * 0.7f;

    // ⚔️ hitbox (atak)
    if (p->action == ACT_ATTACK) {
        int dir = p->facing;
        p->hitbox.w = spriteW * 0.4f;
        p->hitbox.h = spriteH * 0.3f;
        p->hitbox.x = p->x + (dir == 1 ? spriteW : -p->hitbox.w);
        p->hitbox.y = p->y - p->z + spriteH * 0.35f;
    } else {
        p->hitbox.w = 0;
        p->hitbox.h = 0;
    }
}

void updatePlayer(Player* p, float dt) {

    // ⏱️ INVINCIBILITY TIMER
    if (p->invincible) {
        p->invincibleTimer -= dt;
    if (p->invincibleTimer <= 0.0f) {
        p->invincible = false;
        p->invincibleTimer = 0.0f;
        }
    }

    updatePlayerHitboxes(p);

    // JEŚLI ATAK TRWA — NIC INNEGO NIE RÓB
if (p->action == ACT_ATTACK) {
    updateAnimation(&p->attack, dt);

    // jeśli animacja ataku się skończyła
    if (p->attack.frame == p->attack.frames - 1) {
        p->action = (p->vx != 0) ? ACT_WALK : ACT_IDLE;
        p->attack.frame = 0;
        p->attack.timer = 0;
    }
    return;
}
    
    p->x += p->vx * dt;

    p->vz -= GRAVITY * dt;
    p->z += p->vz;

    if (p->z < 0) {
        p->z = 0;
        p->vz = 0;
    }

    if (p->action != ACT_ATTACK) {
    if (p->vx != 0)
        p->action = ACT_WALK;
    else
        p->action = ACT_IDLE;
}

    // ⏱️ combo timer
    if (p->combo > 0) {
        p->comboTimer -= dt;
        if (p->comboTimer <= 0.0f) {
            p->combo = 0;   // reset combo
        }
    }

   if (p->action == ACT_WALK)
        updateAnimation(&p->walk, dt);
    else if (p->action == ACT_ATTACK)
        updateAnimation(&p->attack, dt);
    else
        updateAnimation(&p->idle, dt);
}


