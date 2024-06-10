#include "game.h"

int main(int argc, char* argv[]) {

    Game *game = new Game();
    free(game);
    game = nullptr;
    return 0;
}
