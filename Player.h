#pragma once
#include "Animation.h"
#include "Combo.h"

enum Action {
    ACT_IDLE,
    ACT_WALK,
    ACT_JUMP,
    ACT_ATTACK
};

struct Player {
    float x, y, z;
    float vx, vz;
    int hp;
    int facing;
    Action action;

    Animation idle;
    Animation walk;
    Animation attack;

    ComboBuffer combo;
};

void initPlayer(Player* p);
void updatePlayer(Player* p, float dt);
