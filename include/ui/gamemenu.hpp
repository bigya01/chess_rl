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

    enum TimeIndex
    {
        One = 0,
        Ten,
        Thirty
    };

private:
    sf::RenderWindow &window;
    sf::Font font;
    
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Game *gameRef;

    sf::Text title, singlePlayer, multiPlayer, exit, timeText, time[3];

    int selectedTime = TimeIndex::Ten;
    int timeIn[3] = {1, 10, 30};

};