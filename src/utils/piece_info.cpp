#include "utils/piece_info.hpp"

bool Piece::isColor(int piece, int color)
{
    return (piece & color) == color;
}

int Piece::color(int piece)
{
    return piece & colorMask;
}

int Piece::type(int piece)
{
    return piece & typeMask;
}

bool Piece::isSliding(int piece)
{
    return (piece & 0b100) != 0;
}

bool Piece::isRookQueen(int piece)
{
    return (piece & 0b110) == 0b110;
}

bool Piece::isBishopQueen(int piece)
{
    return (piece & 0b101) == 0b101;
}


std::map<char,int> Piece::pieceFromSymbol = {
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