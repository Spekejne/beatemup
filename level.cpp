#include "Level.h"
#include <stdio.h>

void loadLevel(const char* path, Enemy* e, int* count) {
    FILE* f = fopen(path, "r");
    if (!f) return;

    fscanf(f, "%d", count);
    for (int i = 0; i < *count; i++) {
        fscanf(f, "%f", &e[i].x);
        initEnemy(&e[i]);
    }
    fclose(f);
}
