#include <iostream>
#include "game.hpp"

using namespace std;

int main()
{
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