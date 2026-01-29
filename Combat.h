#pragma once
#include "Player.h"
#include "Enemy.h"

void handleCombat(Player* p, Enemy* e, int count);
bool intersects(const Hitbox& a, const Hitbox& b);
