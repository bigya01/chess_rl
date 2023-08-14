#include "logic/board_state.hpp"
#include "utils/piece.hpp"
#include <map>
#include <string>

BoardState::BoardState()
{
    loadfromFen(startFen);
}

void BoardState::loadfromFen(std::string fen)
{
    


    int file = 0, rank = 7;
    std::string fenString = fen.substr(0, fen.find(' '));
    for (char c : fen)
    {
        if (c == '/')
        {
            file = 0;
            rank--;
        }
        else if (isdigit(c))
        {
            file += c - '0';
        }
        else
        {
            *board[rank*8 +file] = Piece::pieceFromSymbol[c];
            file++;
        }
    }

}