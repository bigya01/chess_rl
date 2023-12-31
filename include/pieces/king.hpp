#include "logic/piece.hpp"

class King : public Piece
{
public:
    King(Coordinate pos, bool isColorWhite);
    ~King() override;
    Piece *clone() override;
    int generateAllMoves(const BoardState &state,
                         std::vector<Move> &moves);
};