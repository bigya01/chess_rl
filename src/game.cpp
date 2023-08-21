#include "game.hpp"
#include "ui/board.hpp"
#include <SFML/Graphics.hpp>
#include "ui/gamemenu.hpp"

Game::Game() {}

void Game::init()
{
    try
    {
        mWindow.create(sf::VideoMode(1280, 800), "Chess");
        isRunning = true;
        GameMenu *menu = new GameMenu(this);
        stateMachine.AddState(menu);
    }
    catch (...)
    {
        isRunning = false;
    }
}
Game::~Game() {}

bool Game::running()
{
    return isRunning;
}

void Game::run()
{
    while (isRunning)
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            isRunning = false;
        else
            stateMachine.GetActiveState()->handleInput(event);
    }
}

void Game::update()
{
    count++;
    stateMachine.GetActiveState()->update();
}

void Game::render()
{
    mWindow.clear();
    stateMachine.GetActiveState()->render();
    mWindow.display();
}
void Game::exitGame()
{
    this->isRunning = false;
}

void Game::createGameBoard(int _startTime, bool useEngine)
{
    stateMachine.AddState(
        new ChessBoard(this, "Player1", "Player2", _startTime, useEngine), true);
}

void Game::goBackToMenu()
{
    stateMachine.AddState(new GameMenu(this), true);
}
