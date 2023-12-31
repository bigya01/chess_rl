#include "logic/board_state.hpp"
#include "logic/piece.hpp"

Piece *BoardState::getPiece(Coordinate location)
{
    return board[location.i][location.j];
}

Piece *BoardState::getPiece(int id)
{
    for (int i = 0; i < 2; i++)
    {
        for (Piece *p : players[i]->pieces)
        {
            if (p->getID() == id)
            {
                return p;
            }
        }
    }

    return nullptr;
}
bool BoardState::isPieceWhite(Coordinate location) const
{
    return board[location.i][location.j]->isWhite();
}
int BoardState::getId(Coordinate location) const
{
    return board[location.i][location.j]->getID();
}

bool BoardState::isEmpty(Coordinate location) const
{
    if (!location.isValidBoardIndex())
    {
        return false;
    }
    if (board[location.i][location.j])
    {
        return false;
    }
    else
        return true;
}

BoardState::~BoardState()
{
    if (players[0] && players[1])
    {
        delete players[0];
        delete players[1];
    }
}

// Copy Constructor
BoardState::BoardState(const BoardState &s)
    : enPassantAvailable(s.enPassantAvailable), enPassant(s.enPassant),
      isWhiteTurn(s.isWhiteTurn), dragPieceId(s.dragPieceId),
      dragPieceLocation(s.dragPieceLocation)
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = nullptr;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        CastleAvailability[i] = s.CastleAvailability[i];
    }

    for (int i = 0; i < 2; i++)
    {
        players[i] = new Player(s.players[i]->getName(), s.players[i]->isWhite());
        for (Piece *p : s.players[i]->pieces)
        {
            Piece *newP = p->clone();
            players[i]->pieces.push_back(newP);
            Coordinate destination = newP->getCoordinate();
            if (!newP->isCaptured())
            {
                board[destination.i][destination.j] = newP;
            }
        }
    }
}
BoardState::BoardState()
{
    players[0] = nullptr;
    players[1] = nullptr;
}
