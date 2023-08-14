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
    std::map<char,int> pieceFromSymbol = {
        {'r', Piece::Black | Piece::Rook},
        {'n', Piece::Black | Piece::Knight},
        {'b', Piece::Black | Piece::Bishop},
        {'q', Piece::Black | Piece::Queen},
        {'k', Piece::Black | Piece::King},
        {'p', Piece::Black | Piece::Pawn},
        {'R', Piece::White | Piece::Rook},
        {'N', Piece::White | Piece::Knight},
        {'B', Piece::White | Piece::Bishop},
        {'Q', Piece::White | Piece::Queen},
        {'K', Piece::White | Piece::King},
        {'P', Piece::White | Piece::Pawn},
    };


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
            *board[rank*8 +file] = pieceFromSymbol[c];
            file++;
        }
    }

}