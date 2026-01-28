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
        0.12f
    );
    initAnimation(
        &p->walk,
        renderer,
        "assets/player_walk.bmp",
        6,        // liczba klatek
        24, 32,   // rozmiar klatki
        0.1f      // trochę szybciej niż idle
    );
    //initAnimation(&p->attack, renderer, "assets/player_attack.bmp", 3, 96, 96, 0.1f);
}

void updatePlayer(Player* p, float dt) {
    p->x += p->vx * dt;

    p->vz -= GRAVITY * dt;
    p->z += p->vz;

    if (p->z < 0) {
        p->z = 0;
        p->vz = 0;
    }

    if (p->action == ACT_WALK)
        updateAnimation(&p->walk, dt);
    else if (p->action == ACT_ATTACK)
        updateAnimation(&p->attack, dt);
    else
        updateAnimation(&p->idle, dt);
}





