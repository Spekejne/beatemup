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

void handleCombat(Player* p, Enemy* e, int count) {
// ❌ brak ataku = brak kolizji
if (p->action != ACT_ATTACK)
return;


// ❌ brak aktywnego hitboxa
if (p->hitbox.w == 0 || p->hitbox.h == 0)
return;


for (int i = 0; i < count; i++) {
if (!e[i].alive)
continue;


// ✅ PRAWDZIWA KOLIZJA
if (intersects(p->hitbox, e[i].hurtbox)) {

     // 🔥 COMBO
            p->combo++;
            p->comboTimer = 1.2f; // reset czasu combo

            // ⚔️ DAMAGE = base + combo bonus
            int dmg = p->baseDamage + (p->combo / 3);
            // co 3 hity +1 dmg

            e[i].hp -= dmg;

            printf("HIT! combo=%d dmg=%d enemyHP=%d\n",
                   p->combo, dmg, e[i].hp);


// 🧍‍♂️ PLAYER ATAKUJE
    if (p->action == ACT_ATTACK && p->hitbox.w > 0) {

        for (int i = 0; i < count; i++) {
            if (!e[i].alive) continue;

            if (intersects(p->hitbox, e[i].hurtbox)) {
                e[i].hp--;

                if (e[i].hp <= 0) {
                    e[i].alive = false;   // 👈 ZNIKA
                }
            }
        }
    }

    // 👾 ENEMY ATAKUJE PLAYERA
    for (int i = 0; i < count; i++) {
        if (!e[i].alive) continue;

        if (e[i].hitbox.w > 0 &&
            intersects(e[i].hitbox, p->hurtbox)) {

            if (!p->invincible) {
                p->hp -= e[i].attackDamage;
                p->invincible = true;
                p->invincibleTimer = 0.6f; // i-frames
            }
        }
    }
}
}
}



