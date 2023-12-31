#pragma once
#include "logic/piece.hpp"
#include "utils/structures.hpp"

class ChessBoard;
class Engine;
struct BoardState;
class Player
{
public:
  Player(std::string playerName, bool isPlayerColorWhite);
  ~Player();

  bool isWhite();
  std::string getName();
  // void addPiece(Piece *p);
  friend class ChessBoard;
  friend class Engine;
  friend struct BoardState;

private:
  std::string Name;
  std::vector<Piece *> pieces;
  bool _isWhite;

  int time;
};
