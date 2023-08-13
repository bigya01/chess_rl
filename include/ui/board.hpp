#pragma once
#include <SFML/Graphics.hpp>

class ChessBoard
{
private:
    sf::RectangleShape mBoard[8][8];
    void initBoard();
public:
    ChessBoard();
    void display(sf::RenderWindow &window);
};