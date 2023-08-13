#include "ui/board.hpp"
#include <SFML/Graphics.hpp>

ChessBoard::ChessBoard()
{
    initBoard();
}

void ChessBoard::initBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            mBoard[i][j].setSize(sf::Vector2f(50, 50));
            mBoard[i][j].setPosition(sf::Vector2f(i * 50, j * 50));
            if ((i + j) % 2 == 0)
            {
                mBoard[i][j].setFillColor(sf::Color::White);
            }
            else
            {
                mBoard[i][j].setFillColor(sf::Color::Black);
            }
        }
    }
}

void ChessBoard::display(sf::RenderWindow &window)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            window.draw(mBoard[i][j]);
        }
    }
}