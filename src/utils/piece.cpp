#include "utils/piece.hpp"

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