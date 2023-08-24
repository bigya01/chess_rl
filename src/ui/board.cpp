#include "ui/board.hpp"
#include "game.hpp"
#include "logic/piece.hpp"
#include <SFML/Graphics.hpp>
#include "logic/engine.hpp"

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define TEST_FEN "rnbqk2r/pp1ppppp/8/3N4/2p1P3/8/PPP2PPP/R1BQKB1R w KQkq - 0 1"

#define FPS 60

namespace Promotion
{
    std::map<int, promotion> promotionMap{
        {0, None}, {1, Queen}, {2, Bishop}, {3, Knight}, {4, Rook}};
}

void clockTickToTime(int clock, int timeInfo[4]);
std::string scoreToString(float score);

ChessBoard::ChessBoard(Game *_gameRef, std::string name1, std::string name2,
                       int _startTimeInMinutes, bool _useEngine)
    : gameRef(_gameRef), startTime(_startTimeInMinutes), window(_gameRef->mWindow)
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
    setBoard();
    buffers[0].loadFromFile("assets/sounds/alert.wav");
    buffers[1].loadFromFile("assets/sounds/capture.wav");
    buffers[2].loadFromFile("assets/sounds/checkmate.wav");
    buffers[3].loadFromFile("assets/sounds/moveb.wav");
    buffers[4].loadFromFile("assets/sounds/movew.wav");
    for (int i = 0; i < 5; i++)
    {
        sounds[i].setBuffer(buffers[i]);
        sounds[i].setVolume(100);
    }
    font.loadFromFile("assets/fonts/jost.ttf");

    frame.loadFromFile("assets/images/framee.png");
    // Create a sprite using the loaded texture
    frameSprite1.setTexture(frame);

    // Set the position of the sprite
    frameSprite1.setPosition(10, 15); // Set the desired position (x, y)
    frameSprite1.setScale(0.5f, 0.5f);

    // Create a sprite using the loaded texture
    frameSprite2.setTexture(frame);

    // Set the position of the sprite
    frameSprite2.setPosition(1030, 535); // Set the desired position (x, y)
    frameSprite2.setScale(0.5f, 0.5f);

    bfont.loadFromFile("assets/fonts/Jost-SemiBold.ttf");
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
    head1.setFont(bfont);
    head1.setCharacterSize(35);
    head1.setFillColor(sf::Color(0x253747FF)); // Hexadecimal color: #FF3366
    head1.setPosition(45, 40);

    // player1
    player1.setFont(font);
    player1.setCharacterSize(30);
    player1.setFillColor(sf::Color(0x1B5233FF)); // Hexadecimal color: #FF3366
    player1.setPosition(45, 90);

    // head2
    head2.setFont(bfont);
    head2.setCharacterSize(35);
    head2.setFillColor(sf::Color(0x253747FF)); // Hexadecimal color: #FF3366
    head2.setPosition(1070, 700);

    // player2
    player2.setFont(font);
    player2.setCharacterSize(30);
    player2.setFillColor(sf::Color(0x1B5233FF)); // Hexadecimal color: #FF3366
    player2.setPosition(1070, 600);

    winner.setFont(bfont);
    winner.setCharacterSize(40);
    winner.setFillColor(sf::Color(0x7A3838FF)); // Hexadecimal color: #FF3366
    winner.setStyle(sf::Text::Bold);            // Set the player1 style to bold
    winner.setPosition(1030, 40);

    piecesTexture.loadFromFile("assets/images/pieces.png");
    piecesTexture.setSmooth(true);
    moveHint.setRadius(15);
    // moveHint.setPointCount(4);
    // moveHint.setFillColor(sf::Color(0x1B5233FF));
    moveHint.setOutlineThickness(3);
    // moveHint.setOutlineColor(sf::Color(0x35a163FF));
}

void ChessBoard::handleInput(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        handleMousePressed(event);
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        handleMouseReleased(event);
    }
}

void ChessBoard::handleMousePressed(sf::Event &event)
{

    int col = (event.mouseButton.x - 320) / tileSize;
    int row = (event.mouseButton.y - 60) / tileSize;
    Coordinate location(row, col);
    if (lastMoveState != lastMoveInfo::None &&
        lastMoveState != lastMoveInfo::Check)
    {
        return;
    }
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        if (location.isValidBoardIndex())
        {
            if (promotionInfo.promotion)
            {
                if (location.j != promotionInfo.location.j)
                {
                    return;
                }

                int direction = state.isWhiteTurn ? 1 : -1;

                for (int i = 0; i < 4; i++)
                {
                    if (location.i == promotionInfo.location.i + direction * i)
                    {
                        moves.push_back({state.dragPieceLocation, promotionInfo.location,
                                         Promotion::promotionMap[i + 1]});
                        makeMove(promotionInfo.location, i + 1);

                        promotionInfo.promotion = false;

                        if (useEngine && enginePlaysWhite == state.isWhiteTurn)
                        {
                            ChessBoard::engineMove();
                        }
                        break;
                    }
                }
                return;
            }
            Piece *piece = state.getPiece(location);
            if (piece)
            {

                // If it is not the player's turn, do nothing
                if (piece->isWhite() != state.isWhiteTurn)
                {
                    return;
                }

                state.dragPieceId = piece->getID();
                state.dragPieceLocation = location;
                Engine::getMoveList(location, allMoves, moves);
            }
        }
    }
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
    }
}

void ChessBoard::handleMouseReleased(sf::Event &event)
{
    int col = (event.mouseButton.x - 320) / tileSize;
    int row = (event.mouseButton.y - 60) / tileSize;
    Coordinate location(row, col);
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (buttonex.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            ChessBoard::goToMainMenu();
            return;
        }
        if (buttonresign.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            if (!(lastMoveState == lastMoveInfo::CheckMate ||
                  lastMoveState == lastMoveInfo::Draw))
                // sounds[2].play();
                ChessBoard::resign();
        }
        if (lastMoveState != lastMoveInfo::None &&
            lastMoveState != lastMoveInfo::Check)
        {
            if (buttonreset.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                resetBoard();
            }
            return;
        }
        bool success = makeMove(location);
        moves.clear();

        if (success)
        {
            hasPlayedMove[state.isWhiteTurn] = true;
            if (useEngine && enginePlaysWhite == state.isWhiteTurn)
            {
                ChessBoard::engineMove();
            }
        }
    }
    state.dragPieceId = 0;
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
        char c = 'a' + i - 1;
        std::string s(1, c);
        sf::Text ltext(std::to_string(i), font, 24);
        ltext.setPosition(280, (tileSize * i) + 15);
        sf::Text rtext(s, font, 24);
        rtext.setPosition((i * tileSize) + 280, 30);
        // Draw the player1
        window.draw(ltext);
        window.draw(rtext);
    }
    //   pieces rendering
    // std::cout << state.players[0]->pieces.size();
    int capturedPieceOffset[2] = {0, 0};
    int capturedPieceOffsetHeight[2] = {0, 0};

    // resetScoreTexture();

    for (int i = 0; i < 2; i++)
    {
        // std::cout << state.players[i]->getName();
        for (Piece *piece : state.players[i]->pieces)
        {
            sf::Sprite sprite;
            sprite.setTexture(piecesTexture);

            // Calculate texture rectangle based on piece properties
            int textureColumn = piece->getTextureColumn();
            int textureRow = piece->isWhite() ? 0 : 1; // Assuming white is row 0, black is row 1
            sprite.setTextureRect(sf::IntRect(textureColumn * 45, textureRow * 45, 45, 45));
            sprite.setScale(64 / sprite.getLocalBounds().width, 64 / sprite.getLocalBounds().height);

            // Set the position of the sprite

            if (piece->isCaptured())
            {
                int index = piece->isWhite();
                int x = index ? capturedPieceOffset[index] * 64 + 20 : capturedPieceOffset[index] * 64 + 1015;
                int y = index ? capturedPieceOffsetHeight[index] * 64 + 275 : capturedPieceOffsetHeight[index] * 64 + 275;
                capturedPieceOffset[index]++;
                if (capturedPieceOffset[index] == 4)
                {
                    capturedPieceOffset[index] = 0;
                    capturedPieceOffsetHeight[index]++;
                }
                sprite.setPosition(x, y);
                window.draw(sprite);
            }
            else if (!(piece->getID() == state.dragPieceId))
            {
                Coordinate tempCor = piece->getCoordinate();
                sprite.setPosition((tempCor.j * tileSize) + 330, (tempCor.i * tileSize) + 70);
                window.draw(sprite);
            }
        }
    }
    for (Move move : moves)
    {
        if (state.isEmpty(move.endPos) &&
            !(state.enPassantAvailable && state.enPassant == move.endPos))
        {
            moveHint.setFillColor(sf::Color(0x1B5233FF));
            moveHint.setOutlineColor(sf::Color(0x35a163FF));
        }
        else
        {
            moveHint.setFillColor(sf::Color(0xFF0000FF));
            moveHint.setOutlineColor(sf::Color(0xFFFFFFFF));
        }
        moveHint.setPosition((move.endPos.j * tileSize) + 347.5, (move.endPos.i * tileSize) + 87.5);
        window.draw(moveHint);
    }

    Piece *dragPiece = state.getPiece(state.dragPieceId);
    if (dragPiece)
    {
        sf::Sprite sprite;
        sprite.setTexture(piecesTexture);
        sprite.setTextureRect(sf::IntRect(dragPiece->getTextureColumn() * 45, (dragPiece->isWhite() ? 0 : 1) * 45, 45, 45));
        sprite.setScale(64 / sprite.getLocalBounds().width, 64 / sprite.getLocalBounds().height);
        sprite.setPosition(sf::Mouse::getPosition(window).x - 32, sf::Mouse::getPosition(window).y - 32);
        window.draw(sprite);
    }
    for (int i = 0; i < 2; i++)
    {
        if ((lastMoveState == lastMoveInfo::CheckMate ||
             lastMoveState == lastMoveInfo::OutofTime ||
             lastMoveState == lastMoveInfo::Resign) &&
            state.isWhiteTurn == i)
        {
            // sounds[0].play();
            winner.setString(PlayerNames[i] + "\nWins!!");
        }

        int numsToDisplay[4] = {0, 0, 0, 0};
        clockTickToTime(playerTime[i] / FPS, numsToDisplay);
        timeStr[i] = std::to_string(numsToDisplay[0]) +
                     std::to_string(numsToDisplay[1]) + ":" +
                     std::to_string(numsToDisplay[2]) +
                     std::to_string(numsToDisplay[3]);
    }
    resetScoreTexture();

    switch (lastMoveState)
    {
    case lastMoveInfo::OutofTime:
        sounds[0].play();
        winner.setString(PlayerNames[state.isWhiteTurn] + "\nWins!!\nOut of Time");
        break;
    case lastMoveInfo::CheckMate:
        sounds[1].play();
        winner.setString(PlayerNames[!state.isWhiteTurn] + "\nWins!!\nCheckmate");
        break;
    case lastMoveInfo::Draw:
        sounds[0].play();
        winner.setString("Draw!!");
        break;
    case lastMoveInfo::Resign:
        sounds[0].play();
        winner.setString(PlayerNames[state.isWhiteTurn] + "\nWins!!\nResigned.");
        break;
    case lastMoveInfo::Check:
        // sounds[0].play();
        winner.setString("Check!!");
        break;
    default:
        winner.setString("");
        break;
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
    state = BoardState();
    promotionInfo.promotion = false;
    state.players[0] = new Player(PlayerNames[0], true);
    state.players[1] = new Player(PlayerNames[1], false);
    hasPlayedMove[0] = false;
    hasPlayedMove[1] = false;
    resetScoreTexture();

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

bool ChessBoard::makeMove(Coordinate location, int promotionID)
{

    Promotion::promotion promotion = Promotion::None;
    // handlePromotionindex
    if (promotionID >= 0 && promotionID <= 4)
    {
        promotion = Promotion::promotionMap[promotionID];
    }
    Coordinate temp = state.dragPieceLocation;
    lastMoveInfo info = Engine::handlePiecePlacement(location, state, moves,
                                                     promotionInfo, promotion);

    moves.clear();
    if (info.success)
    {
        // SoundManager::playSound(!state.isWhiteTurn ? SoundManager::WhiteMove
        //    : SoundManager::BlackMove);
        state.isWhiteTurn ? sounds[4].play() : sounds[3].play();
        lastMoveState = info.state;
        lastMove.made = true;
        lastMove.startPos = temp;
        lastMove.endPos = location;
        int count = Engine::generateAllMoves(state, allMoves);
        if (count == 0)
        {
            if (info.state == lastMoveInfo::Check)
            {
                lastMoveState = lastMoveInfo::CheckMate;
                // sounds[2].play();
                std::cout << "Checkmate!!!" << std::endl;
                score[state.isWhiteTurn] += 1;
            }
            else
            {
                // sounds[0].play();
                lastMoveState = lastMoveInfo::Draw;
                score[0] += 0.5;
                score[1] += 0.5;
            }
            resetScoreTexture();
        }
    }
    return info.success;
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
    resetScoreTexture();
    enginePlaysWhite = !enginePlaysWhite;

    delete state.players[0];
    delete state.players[1];
    setBoard();
}

void ChessBoard::resetScoreTexture()
{
    head2.setString(PlayerNames[0]);
    head1.setString(PlayerNames[1]);
    player2.setString("Score: " + scoreToString(score[0]) + "\nTiming: " + timeStr[0]);
    player1.setString("Score: " + scoreToString(score[1]) + "\nTiming: " + timeStr[1]);
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
            // sounds[2].play();
            lastMoveState = lastMoveInfo::CheckMate;
        }
        else
        {
            // sounds[0].play();
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
