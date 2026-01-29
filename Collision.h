#pragma once
#include "Player.h"
#include "Enemy.h"

bool bodyOverlapY(const Hitbox& a, const Hitbox& b);
void resolveBodyCollision(Player* p, Enemy* e);
