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

void updatePlayer(Player* p, float dt) {

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

   if (p->action == ACT_WALK)
        updateAnimation(&p->walk, dt);
    else if (p->action == ACT_ATTACK)
        updateAnimation(&p->attack, dt);
    else
        updateAnimation(&p->idle, dt);
}













