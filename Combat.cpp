#include "Combat.h"
#include <cmath>

void handleCombat(Player* p, Enemy* e, int count) {
    // tylko gdy gracz atakuje
    if (p->action != ACT_ATTACK)
        return;

    for (int i = 0; i < count; i++) {
        if (!e[i].alive)
            continue;

        float dx = fabs(p->x - e[i].x);

        // prosty hitbox
        if (dx < 40 && e[i].action != EN_HIT && e[i].action != EN_DEAD) {
            e[i].hp--;
            e[i].action = EN_HIT;
            e[i].hit.frame = 0;
            e[i].hit.timer = 0;

            if (e[i].hp <= 0) {
                e[i].action = EN_DEAD;
            }
        }
    }
}
