#pragma once
#include "ui/board.hpp"
#include "utils/structures.hpp"
#include <ctime>
#define ASCII_OFFSET 48

class Test;

class Engine
{
public:
    enum EngineDifficulty
    {
        None,
        Random,
        Evaluated
    };
    static void handleFENString(const std::string fenString, BoardState &state);
    static bool canDirectAttackKing(const BoardState &state);

    static lastMoveInfo handlePiecePlacement(Coordinate &destination, BoardState &state, const std::vector<Move> moves, Promotion::uiInfo &promotionInfo, Promotion::promotion promotionType = Promotion::None);
    static int generateAllMoves(const BoardState &state, std::vector<std::vector<Move>> &allMoves);
    static void getMoveList(const Coordinate &c, std::vector<std::vector<Move>> &allMovesSrc, std::vector<Move> &movesDest);
    static int evaluateState(const BoardState &state);
    static bool placePiece(Move move, BoardState &state);
    static Move *generateAIMove(const BoardState &state,
                                std::vector<std::vector<Move>> &allMoves);
    friend class Test;

private:
    static void addPiece(Piece *piece, BoardState &state);
    static Move *randomAI(const BoardState &state,
                          std::vector<std::vector<Move>> &allMoves);
    static Move *evaluateAI(const BoardState &state,
                            std::vector<std::vector<Move>> &allMoves);
    static int miniMax(BoardState state, int depth, bool isMaximizing, int alpha,
                       int beta);
};