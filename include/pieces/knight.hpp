#pragma once

#include "logic/piece.hpp"

class Knight : public Piece
{
public:
    Knight(Coordinate pos, bool isColorWhite);
    ~Knight() override;
    Piece *clone() override;
    int generateAllMoves(const BoardState &state,
                         std::vector<Move> &moves) override;
};
