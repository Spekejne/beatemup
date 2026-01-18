#include "Game.h"

int main() {
    if (!initGame()) return 1;
    gameLoop();
    shutdownGame();
    return 0;
}
