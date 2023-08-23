#include "ui/board.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include "logic/engine.hpp"

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FPS 144

namespace Promotion
{
    std::map<int, promotion> promotionMap{
        {0, None}, {1, Queen}, {2, Bishop}, {3, Knight}, {4, Rook}};
}

void clockTickToTime(int clock, int timeInfo[4]);
// bool buttonPress(int x, int y, const SDL_Rect &rect);
std::string scoreToString(float score);

ChessBoard::ChessBoard(Game *_gameRef, std::string name1, std::string name2,
                       int _startTimeInMinutes, bool _useEngine)
    : gameRef(_gameRef), startTime(_startTimeInMinutes)
{
    PlayerNames[0] = name1;
    PlayerNames[1] = name2;
    score[0] = score[1] = 0;
    useEngine = _useEngine;
    enginePlaysWhite = false;
}

ChessBoard::~ChessBoard()
{
}

void ChessBoard::init()
{
}

void ChessBoard::handleInput(sf::Event &event)
{
}

void ChessBoard::render()
{
}

void ChessBoard::update()
{
}

void ChessBoard::setBoard()
{
    BoardState state;
    promotionInfo.promotion = false;
    state.players[0] = new Player(PlayerNames[0], true);
    state.players[1] = new Player(PlayerNames[1], false);
    hasPlayedMove[0] = false;
    hasPlayedMove[1] = false;
    // load score texture
    // scoreTexture[0].loadSentence(scoreToString(score[0]), 30,
    //                              TextureManager::darkGreen);
    // scoreTexture[1].loadSentence(scoreToString(score[1]), 30,
    //                              TextureManager::darkGreen);

    // Handle FEN string
    Engine::handleFENString(STARTING_FEN, state);
    lastMoveState = lastMoveInfo::None;
    allMoves.clear();
    lastMove.made = false;
    Engine::generateAllMoves(state, allMoves);

    // Creating Players
    playerTime[0] = playerTime[1] = startTime * 60 * FPS;

    if (enginePlaysWhite && useEngine)
    {
        ChessBoard::engineMove();
    }
}

void ChessBoard::goToMainMenu() { gameRef->goBackToMenu(); }

void ChessBoard::resign()
{
    lastMoveState = lastMoveInfo::Resign;
    score[state.isWhiteTurn] += 1;
}

void ChessBoard::engineMove()
{
    Move *move = Engine::generateAIMove(state, allMoves);
    if (!move)
    {
        return;
    }
    bool check = Engine::placePiece(*move, state);
    lastMoveState = check ? lastMoveInfo::Check : lastMoveInfo::None;

    int count = Engine::generateAllMoves(state, allMoves);
    if (count == 0)
    {
        if (check)
        {
            lastMoveState = lastMoveInfo::CheckMate;
        }
        else
        {
            lastMoveState = lastMoveInfo::Draw;
        }
    }
    lastMove.made = true;
    lastMove.startPos = move->startPos;
    lastMove.endPos = move->endPos;

    delete move;
    return;
}

void clockTickToTime(int clock, int timeInfo[4])
{
    int min, secs;
    min = clock / 60;
    secs = clock % 60;

    timeInfo[0] = min / 10;
    timeInfo[1] = min % 10;
    timeInfo[2] = secs / 10;
    timeInfo[3] = secs % 10;
}

std::string scoreToString(float score)
{
    std::string str;
    str.clear();
    int beforePoint = score;
    if (beforePoint > 99)
    {
        beforePoint = 99;
    }
    str = std::to_string(beforePoint);
    str += '.';
    if ((score - beforePoint) * 2 >= 1)
    {
        str += '5';
    }
    else
    {
        str += '0';
    }
    return str;
}
