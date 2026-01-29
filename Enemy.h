#pragma once
#include "Animation.h"
#include "Player.h"
#include "Hitbox.h"

enum EnemyAction {
    EN_IDLE,
    EN_WALK,
    EN_ATTACK,
    EN_HIT,
    EN_DEAD
};

struct Enemy {
    float x, y;
    float vx;
    int facing;
    int alive;
    int hp;

    EnemyAction action;

    Animation idle;
    Animation walk;
    Animation attack;
    Animation hit;
    Animation dead;

    Hitbox hurtbox;
    Hitbox hitbox;
};

void initEnemy(Enemy* e, float x, float y);
void updateEnemy(Enemy* e, Player* p, float dt);


