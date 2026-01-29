#include "level.h"
#include <fstream>
#include <string>

void loadLevel(const char* path, Enemy* enemies, int* count) {
    std::ifstream f(path);
    std::string type;
    float x, y;
    *count = 0;

    while (f >> type >> x >> y) {
        if (type == "enemy" && *count < 16) {
            initEnemy(&enemies[*count], x, y);
            (*count)++;
        }
    }
}
