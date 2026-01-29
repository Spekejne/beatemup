#include "level.h"
#include <fstream>
#include <string>

void loadLevel(const char* path, Enemy* enemies, int* count) {
    std::ifstream f(path);
    if (!f.is_open()) {
        printf("❌ NIE MOZNA OTWORZYC level.txt\n");
        return;
    }

    std::string type;
    float x, y;
    *count = 0;

    while (f >> type >> x >> y) {
        printf("READ: %s %f %f\n", type.c_str(), x, y);

        if (type == "enemy" && *count < 16) {
            initEnemy(&enemies[*count], x, y);
            (*count)++;
        }
    }

    printf("ENEMIES LOADED: %d\n", *count);
}

