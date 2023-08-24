#pragma once
#include "logic/piece.hpp"
#include "logic/player.hpp"
#include "utils/structures.hpp"

struct BoardState
{
    Piece *board[8][8];
    bool CastleAvailability[4];
    bool enPassantAvailable;
    Coordinate enPassant;

    bool isWhiteTurn;

    int dragPieceId;

    Coordinate dragPieceLocation;

    Player *players[2];

    Piece *getPiece(Coordinate location);
    Piece *getPiece(int id);

    bool isPieceWhite(Coordinate location) const;
    int getId(Coordinate location) const;

    bool isEmpty(Coordinate location) const;
    ~BoardState();
    BoardState(const BoardState &s);
    BoardState();
};
