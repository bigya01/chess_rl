#include <iostream>
#include "game.hpp"
#include "utils/test.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        Test t;
        t.standardPerft(atoi(argv[1]));
        return 0;
    }
    Game *game = nullptr;
    game = new Game();
    game->init();
    while (game->running())
    {
        game->processEvents();
        game->update();
        game->render();
    }
    delete game;
    return 0;
}