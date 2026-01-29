#include "level.h"
#include <fstream>
#include <string>
#include <cstdio>

void loadLevel(const char* path, Enemy* enemies, int* count) {
    std::ifstream f(path);

    if (!f.is_open()) {
        printf("❌ NIE MOZNA OTWORZYC %s\n", path);
        *count = 0;
        return;
    }

    std::string type;
    float x, y;
    *count = 0;

    printf("📄 Wczytywanie levelu: %s\n", path);

    while (f >> type >> x >> y) {
        printf("READ: %s %f %f\n", type.c_str(), x, y);

        if (type == "enemy" && *count < 16) {
            initEnemy(&enemies[*count], x, y);
            (*count)++;
        }
    }

    printf("✅ ENEMIES LOADED: %d\n", *count);
}
