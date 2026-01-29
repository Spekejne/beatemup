#include "Collision.h"
#include "Combat.h"

void resolveBodyCollision(Player* p, Enemy* e)
{
    if (!intersects(p->hurtbox, e->hurtbox))
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
