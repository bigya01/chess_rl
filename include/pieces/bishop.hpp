#pragma once

#include "logic/piece.hpp"

class Bishop : public SlidePiece
{
public:
    Bishop(Coordinate pos, bool isColorWhite);
    Piece *clone() override;
};