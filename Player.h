#pragma once
#include "Animation.h"
#include "Combo.h"
#include "Hitbox.h"

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

    Hitbox hurtbox;
    Hitbox hitbox;

    ComboBuffer combo;
};

void initPlayer(Player* p);
void updatePlayer(Player* p, float dt);

