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
    if (!font.loadFromFile("jost.ttf"))
    {
        // Handle font loading error
        return EXIT_FAILURE;
    }
    if (!frame.loadFromFile("framee.png")) {
        // Error handling if image loading fails
        return EXIT_FAILURE;
    }

    // Create a sprite using the loaded texture
    frameSprite1.setTexture(texture);

    // Set the position of the sprite
    frameSprite1.setPosition(10, 15); // Set the desired position (x, y)
    frameSprite1.setScale(0.5f,0.5f);

    // Create a sprite using the loaded texture
    frameSprite2.setTexture(texture);

    // Set the position of the sprite
    frameSprite2.setPosition(1017, 535); // Set the desired position (x, y)
    frameSprite2.setScale(0.5f,0.5f);






    if (!bfont.loadFromFile("Jost-SemiBold.ttf"))
    {
        // Handle font loading error
        return EXIT_FAILURE;
    }
    // Chessboard
   


    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            tile[row][col].setSize(sf::Vector2f(tileSize, tileSize));
            tile[row][col].setPosition((col * tileSize) + 320, (row * tileSize) + 60);

            if ((row + col) % 2 == 0)
            {
                tile[row][col].setFillColor(sf::Color(0xEAB2A0FF));
            }
            else
            {
                tile[row][col].setFillColor(sf::Color(0x855858FF));
            }
        }
    }
    // reset
    textreset.setString("RESET");
    textreset.setFont(font);
    textreset.setCharacterSize(20);
    textreset.setFillColor(sf::Color(0x35a163FF)); // Hexadecimal color: #FF3366
    textreset.setPosition(118, 577);
    buttonreset.setSize(sf::Vector2f(205, 45));
    buttonreset.setPosition(45, 570);
    buttonreset.setFillColor(sf::Color(0x253747FF)); // Hexadecimal color: #FF3366
    // resign
    textresign.setString("RESIGN");
    textresign.setFont(font);
    textresign.setCharacterSize(20);
    textresign.setFillColor(sf::Color(0x35a163FF)); // Hexadecimal color: #FF3366
    textresign.setPosition(118, 637);
    buttonresign.setSize(sf::Vector2f(205, 45));
    buttonresign.setPosition(45, 630);
    buttonresign.setFillColor(sf::Color(0x253747FF));
    // exit
     textex.setString("EXIT");
    textex.setFont(font);
    textex.setCharacterSize(20);
    textex.setFillColor(sf::Color(0x35a163FF)); // Hexadecimal color: #FF3366
    textex.setPosition(125, 697);
    buttonex.setSize(sf::Vector2f(205, 45));
    buttonex.setPosition(45, 690);
    buttonex.setFillColor(sf::Color(0x253747FF));



    // head1
     head1.setString("PLAYER 1");
     head1.setFont(bfont);
    head1.setCharacterSize(35);
    head1.setFillColor(sf::Color(0x253747FF)); // Hexadecimal color: #FF3366
    head1.setPosition(45, 40);
  
    // player1
    player1.setFont(font);
    player1.setCharacterSize(30);
    player1.setFillColor(sf::Color(0x1B5233FF)); // Hexadecimal color: #FF3366
    player1.setPosition(45, 90);
    player1.setString("SCORE\nTIMING");



      // head2
    head2.setString("PLAYER 2", bfont, 35);
    head2.setFont(bfont);
    head2.setCharacterSize(35);
    head2.setFillColor(sf::Color(0x253747FF)); // Hexadecimal color: #FF3366
    head2.setPosition(1070, 700);

    // player2
    player2.setFont(font);
    player2.setCharacterSize(30);
    player2.setFillColor(sf::Color(0x1B5233FF)); // Hexadecimal color: #FF3366
    player2.setPosition(1070, 600);
    player2.setString("SCORE\nTIMING");

    winner.setFont(font);
    winner.setCharacterSize(40);
    winner.setFillColor(sf::Color(0x7A3838FF)); // Hexadecimal color: #FF3366
    winner.setStyle(sf::Text::Bold);            // Set the player1 style to bold
    winner.setString("PLAYER 1\nWINS");
    winner.setPosition(1070, 40);
}

void ChessBoard::handleInput(sf::Event &event)
{
}

void ChessBoard::render()
{
     window.clear(sf::Color(0x435B66FF));
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
                window.draw(tile[i][j]);
        }
        for (int i = 1; i < 9; i++)
        {
            sf::Text ltext(std::to_string(i), font, 24);
            ltext.setPosition(280, (tileSize * i) + 15);
            sf::Text rtext(std::to_string(i), font, 24);
            rtext.setPosition((i * tileSize) + 280, 30);
            // Draw the player1
            window.draw(ltext);
            window.draw(rtext);
        }
        window.draw(frameSprite1);
        window.draw(frameSprite2);
        window.draw(player1);
        window.draw(player2);
        window.draw(head1);
        window.draw(head2);
        window.draw(buttonreset);
        window.draw(textreset);
        window.draw(buttonresign);
        window.draw(textresign);
        window.draw(buttonex);
        window.draw(textex);
        window.draw(winner);
        
}

void ChessBoard::update()
{
    if ((lastMoveState == lastMoveInfo::None) ||
        (lastMoveState == lastMoveInfo::Check))
    {
        if (!hasPlayedMove[!state.isWhiteTurn])
            return;

        playerTime[!state.isWhiteTurn]--;
        if (playerTime[!state.isWhiteTurn] < 0)
        {
            lastMoveState = lastMoveInfo::OutofTime;
            playerTime[!state.isWhiteTurn] = 0;
            score[0] += 1;
        }
    }
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

void ChessBoard::resetBoard()
{
    // We swap the names, namesTexture and score texture after game is reset
    std::string tempStr;
    float tempInt;
    tempInt = score[1];
    score[1] = score[0];
    score[0] = tempInt;
    tempStr = PlayerNames[1];
    PlayerNames[1] = PlayerNames[0];
    PlayerNames[0] = tempStr;
    // resetScoreTexture();
    enginePlaysWhite = !enginePlaysWhite;

    delete state.players[0];
    delete state.players[1];
    setBoard();
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
