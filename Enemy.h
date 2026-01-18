#pragma once
#include "Animation.h"
#include "Player.h"

struct Enemy {
    float x, y;
    int hp;
    int alive;
    Animation idle;
};

void initEnemy(Enemy* e);
void updateEnemy(Enemy* e, Player* p, float dt);
