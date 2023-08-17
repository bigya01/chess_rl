#pragma once
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "logic/game_state.hpp"

class GameMenu : public GameState
{
public:
    GameMenu(Game *gameRef);
    ~GameMenu() override;
    void init() override;
    void handleInput(sf::Event &event) override;
    void render() override;
    void update() override;

    void loadAssets();
    enum TimeIndex
    {
        One = 0,
        Ten,
        Thirty
    };

private:
    std::string names[2];
    sf::RectangleShape namesBox[2];
    sf::Texture cursorTexture;
    sf::Texture namesPromptTexture[2];
    sf::Texture namesTexture[2];

    bool isNameOneTheFocus;
    bool displayCursor;
    int count;
    TimeIndex timeIndex;

    sf::RectangleShape singleButton, twoButton, exitButton,
        backdrop, square, squar, min, tenmin, thirtymin;
    sf::Texture singleTexture, twoTexture, exitTexture, backdropTexture,
        squareTexture, squarTexture;
    sf::Texture minTexture[2], tenminTexture[2], thirtyminTexture[2];

    Game *gameRef;
};