#pragma once

#include <SFML/Graphics.hpp>
#include <utils/state_machine.hpp>

namespace GameInfo
{
    enum State
    {
        menu,
        board,
        gameover
    };
};

class Game
{
public:
    Game();
    ~Game();
    void init();
    void run();
    void processEvents();
    void update();
    void render();
    void clean();
    void exitGame();

    bool running();

    void createGameBoard(int _startTime = 10, bool _useEngine = false);
    void goBackToMenu();
    sf::RenderWindow mWindow;

private:
    bool isRunning;
    StateMachine stateMachine;
    GameInfo::State state;
    int count = 0;
};