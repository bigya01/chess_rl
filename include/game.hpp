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

    void createGameBoard(std::string name0, std::string name1, int _startTime = 10, bool _useEngine = false);
    void goBackToMenu();

private:
    bool isRunning;
    sf::RenderWindow mWindow;
    StateMachine stateMachine;
    GameInfo::State state;
    int count = 0;
};