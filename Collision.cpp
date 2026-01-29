#include "Collision.h"
#include "Combat.cpp"

void resolveBodyCollision(Player* p, Enemy* e) {
    if (!intersects(p->hurtbox, e->hurtbox))
        return;

    float overlapLeft  = (p->hurtbox.x + p->hurtbox.w) - e->hurtbox.x;
    float overlapRight = (e->hurtbox.x + e->hurtbox.w) - p->hurtbox.x;

    float push = (overlapLeft < overlapRight) ? overlapLeft : -overlapRight;

    p->x -= push * 0.5f;
    e->x += push * 0.5f;
}
