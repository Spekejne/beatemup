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


// ❌ enemy już trafiony / martwy
if (e[i].action == EN_HIT || e[i].action == EN_DEAD)
continue;


// ✅ PRAWDZIWA KOLIZJA
if (intersects(p->hitbox, e[i].hurtbox)) {


e[i].hp--;
e[i].action = EN_HIT;


// reset animacji hit
e[i].hit.frame = 0;
e[i].hit.timer = 0;


// 💀 śmierć
if (e[i].hp <= 0) {
e[i].action = EN_DEAD;
e[i].dead.frame = 0;
e[i].dead.timer = 0;
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
