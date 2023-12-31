#include "pieces/bishop.hpp"
#include "utils/structures.hpp"

Bishop::Bishop(Coordinate pos, bool isColorWhite)
    : SlidePiece(pos, isColorWhite)
{

  textureColumn = 2;
  loopStartIndex = 4;
  loopStopIndex = 8;
}

Piece *Bishop::clone() { return new Bishop(*this); }
