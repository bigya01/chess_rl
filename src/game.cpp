#include "game.hpp"
#include "ui/board.hpp"
#include <SFML/Graphics.hpp>

Game::Game(){
    mWindow.create(sf::VideoMode(640, 480), "Chess");
}

void Game::run(){
    while (mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents(){
    sf::Event event;
    while (mWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Game::update(){
}

void Game::render(){
    mWindow.clear();
    ChessBoard board;
    board.display(mWindow);
    mWindow.display();
}