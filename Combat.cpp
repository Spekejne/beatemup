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

    // 👾 ENEMY ATAKUJE GRACZA
for (int i = 0; i < count; i++) {
    if (!e[i].alive)
        continue;

    // enemy musi atakować
    if (e[i].action != EN_ATTACK)
        continue;

    // brak hitboxa
    if (e[i].hitbox.w == 0 || e[i].hitbox.h == 0)
        continue;

    // kolizja
    if (intersects(e[i].hitbox, p->hurtbox)) {

        // ⚠️ NIE co klatkę – tylko raz na animację
        if (!p->invincible) {
            p->hp--;
            p->invincible = true;
            p->invincibleTimer = 0.6f; // pół sekundy
        }
    }
}
}



