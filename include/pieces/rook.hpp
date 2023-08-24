#include "logic/piece.hpp"

class Rook : public SlidePiece
{
public:
  Rook(Coordinate pos, bool isColorWhite);
  Piece *clone() override;

private:
};
