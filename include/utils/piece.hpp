#pragma once

class Piece{
public:
    static const int None = 0;
    static const int King = 1;
    static const int Pawn = 2;
    static const int Knight = 3;
    static const int Bishop = 4;
    static const int Rook = 5;
    static const int Queen = 6;
    static const int White = 8;
    static const int Black = 16;
    bool isColor(int piece, int color);
    int color(int piece);
    int type(int piece);
    bool isSliding(int piece);
    bool isRookQueen(int piece);
    bool isBishopQueen(int piece);
private:
    const int typeMask = 0b00111;
    const int whiteMask = 0b10000;
    const int blackMask = 0b01000;
    const int colorMask = whiteMask | blackMask;
};