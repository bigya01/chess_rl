#pragma once
#include "utils/piece.hpp"
#include <string>

class BoardState
{
private:
    const std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    int *board[64];
public:
    BoardState();
    void loadfromFen(std::string fen);
};