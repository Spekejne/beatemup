#include "Combat.h"
#include <cmath>

bool intersects(const Hitbox& a, const Hitbox& b) {
    return (
        a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y
    );
}

void handleCombat(Player* p, Enemy* enemies, int count)
{
    // ==============================
    // PLAYER ATAKUJE ENEMY
    // ==============================
    if (p->action == ACT_ATTACK &&
        p->hitbox.w > 0 && p->hitbox.h > 0)
    {
        for (int i = 0; i < count; i++)
        {
            Enemy* e = &enemies[i];
            if (!e->alive) continue;
            if (e->action == EN_DEAD) continue;

            if (intersects(p->hitbox, e->hurtbox))
            {
                e->hp--;
                e->action = EN_HIT;

                e->hit.frame = 0;
                e->hit.timer = 0;

                if (e->hp <= 0)
                {
                    e->action = EN_DEAD;
                    e->dead.frame = 0;
                    e->dead.timer = 0;
                    e->alive = false; // ← KLUCZ
                }
            }
        }
    }

    // ==============================
    // ENEMY ATAKUJE PLAYERA
    // ==============================
    for (int i = 0; i < count; i++)
    {
        Enemy* e = &enemies[i];
        if (!e->alive) continue;
        if (e->action != EN_ATTACK) continue;
        if (e->hitbox.w == 0 || e->hitbox.h == 0) continue;

        if (intersects(e->hitbox, p->hurtbox))
        {
            if (!p->invincible)
            {
                p->hp--;
                p->invincible = true;
                p->invincibleTimer = 0.6f;
            }
        }
    }
}


