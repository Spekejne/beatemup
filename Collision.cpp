#include "Collision.h"
#include "Combat.h"

bool bodyOverlapY(const Hitbox& a, const Hitbox& b)
{
    return a.y < b.y + b.h &&
           a.y + a.h > b.y;
}

void resolveBodyCollision(Player* p, Enemy* e)
{
    if (p->z > 0.0f) return;

    if (!bodyOverLapY(p->hurtbox, e->hurtbox))
        return;

    float pCenter = p->hurtbox.x + p->hurtbox.w * 0.5f;
    float eCenter = e->hurtbox.x + e->hurtbox.w * 0.5f;

    float overlap =
        (p->hurtbox.w * 0.5f + e->hurtbox.w * 0.5f) -
        fabs(pCenter - eCenter);

    if (overlap <= 0.0f)
        return;

    float direction = (pCenter < eCenter) ? -1.0f : 1.0f;

    p->x += direction * overlap * 0.5f;
    e->x -= direction * overlap * 0.5f;
}
