#include "Collision.h"

bool intersects(const Hitbox& a, const Hitbox& b) {
    return (
        a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y
    );
}

void resolveBodyCollision(Player* p, Enemy* e) {
    if (!intersects(p->hurtbox, e->hurtbox))
        return;

    float overlapLeft  = (p->hurtbox.x + p->hurtbox.w) - e->hurtbox.x;
    float overlapRight = (e->hurtbox.x + e->hurtbox.w) - p->hurtbox.x;

    float push = (overlapLeft < overlapRight) ? overlapLeft : -overlapRight;

    p->x -= push * 0.5f;
    e->x += push * 0.5f;
}
