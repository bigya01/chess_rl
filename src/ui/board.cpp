#include "ui/board.hpp"
#include <SFML/Graphics.hpp>

namespace Color{
    sf::Color dark(0xa97a65ff);
    sf::Color light(0xf1d9c0ff);
}

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
            mBoard[i][j].setSize(sf::Vector2f(100, 100));
            mBoard[i][j].setPosition(sf::Vector2f(i * 100 + 240, j * 100));
            if ((i + j) % 2 == 0)
            {
                mBoard[i][j].setFillColor(Color::light);
            }
            else
            {
                mBoard[i][j].setFillColor(Color::dark);
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