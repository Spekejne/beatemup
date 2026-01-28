#pragma once
#include "Animation.h"

enum EnemyAction {
    EN_IDLE,
    EN_WALK
};

struct Enemy {
    float x, y;
    float vx;
    int facing;
    int alive;

    EnemyAction action;

    Animation idle;
    Animation walk;
};
