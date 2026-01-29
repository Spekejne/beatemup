#include "Combat.h"

void handleCombat(Player* p, Enemy* e, int count) {
    if (p->action != ACT_ATTACK) return;

    for (int i = 0; i < count; i++) {
        if (!e[i].alive) continue;

        if (p->x + 64 > e[i].x && p->x < e[i].x + 64) {
            e[i].hp--;
            if (e[i].hp <= 0) e[i].alive = 0;
        }
    }

    if (player.action == ACT_ATTACK) {
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i].alive) continue;

        float dx = fabs(player.x - enemies[i].x);
        if (dx < 40 && enemies[i].action != EN_HIT) {
            enemies[i].hp--;
            enemies[i].action = EN_HIT;
            enemies[i].hit.frame = 0;
            enemies[i].hit.timer = 0;
        }
    }
}
}

