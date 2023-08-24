#pragma once
#include <SFML/Graphics.hpp>
#include <logic/game_state.hpp>
#include <logic/board_state.hpp>
#include <game.hpp>
#include "utils/sound_manager.hpp"
#include <list>

class ChessBoard : public GameState
{

public:
    ChessBoard(Game *_gameRef, std::string name1 = "Bindu", std::string name2 = "Krishant", int _startTime = 10, bool _useEngine = false);
    ~ChessBoard() override;

    void init() override;
    void setBoard();
    void resetBoard();

    // handleEvents
    void handleInput(sf::Event &event) override;
    void handleMouseReleased(sf::Event &event);
    void handleMousePressed(sf::Event &event);

    bool makeMove(Coordinate location, int promotionType = 0);

    void update() override;
    void render() override;

    void engineMove();

    void goToMainMenu();

    void resign();

private:
    SoundManager soundManager;
    Game *gameRef;
    sf::RenderWindow &window;
    BoardState state;
    Coordinate boardStartPos;
    std::vector<Move> moves;
    std::vector<std::vector<Move>> allMoves;
    Promotion::uiInfo promotionInfo;
    lastMoveInfo::State lastMoveState;

    float score[2] = {0, 0};
    sf::Texture scoreTexture[2];
    void resetScoreTexture();

    bool useEngine;
    bool enginePlaysWhite;

    LastMove lastMove;
    Player *players[2];
    int playerTime[2];
    std::string PlayerNames[2];
    bool hasPlayedMove[2];
    int startTime;
    // std::list<sf::Sprite> pieceSprites; // List to store piece sprites
    // sf::Sprite* selectedSprite = nullptr; // Keep track of the selected sprite
    // sf::Vector2f offset; // Offset between mouse and sprite

    // ui
    std::string timeStr[2];
    sf::Font font;
    sf::Font bfont;
    sf::Texture frame;
    sf::Sprite frameSprite1;
    sf::Sprite frameSprite2;
    int gridSize = 8;
    int tileSize = 85;
    sf::RectangleShape tile[8][8];
    sf::Text textreset, textresign, textex, head1, head2, player1, player2, winner;
    sf::RectangleShape buttonreset, buttonresign, buttonex;
    sf::Texture piecesTexture;
    sf::CircleShape moveHint;



    // UI
    sf::RectangleShape resetButton, exitButton, resignButton;
    sf::Texture horizontalNotation[8];
    sf::Texture verticalNotation[8];
    sf::Texture playerNamesTexture[2]; // Stores the texture of player
    sf::Texture resetButtonTexture;
    sf::Texture checkTexture, checkMateTexture, outOfTimeTexture, matchDrawTexture,
        blackResignTexture, whiteResignTexture;
    sf::Texture numberTextures[10]; // Stores the textures for numbers 0-9
    sf::Texture wonTexture;
    sf::Texture colonTexture;
    sf::Texture pieceTexture; // Stores texture of all pieces
    sf::Texture exitButtionTexture;
    sf::Texture resignButtonTexture;
    sf::Texture scoreboardTexture;
};