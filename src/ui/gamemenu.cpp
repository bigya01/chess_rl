#include "ui/gamemenu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

GameMenu::GameMenu(Game *_gameRef) : gameRef(_gameRef), window(_gameRef->mWindow)
{
    font.loadFromFile("assets/fonts/jost.ttf");
}

GameMenu::~GameMenu()
{
}

void GameMenu::init()
{
    backgroundTexture.loadFromFile("assets/images/bg.jpeg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(1280) / backgroundTexture.getSize().x,
                              static_cast<float>(800) / backgroundTexture.getSize().y);

    title.setFont(font);
    title.setString("Chess");
    title.setPosition(200, 250);
    title.setCharacterSize(120);
    title.setFillColor(sf::Color::Black);

    singlePlayer.setFont(font);
    singlePlayer.setString("Single Player");
    singlePlayer.setPosition(750, 100);
    singlePlayer.setCharacterSize(50);
    singlePlayer.setFillColor(sf::Color::Black);

    multiPlayer.setFont(font);
    multiPlayer.setString("Multi Player");
    multiPlayer.setPosition(750, 200);
    multiPlayer.setCharacterSize(50);
    multiPlayer.setFillColor(sf::Color::Black);

    exit.setFont(font);
    exit.setString("Exit");
    exit.setPosition(750, 400);
    exit.setCharacterSize(50);
    exit.setFillColor(sf::Color::Black);

    timeText.setFont(font);
    timeText.setString("Time:");
    timeText.setPosition(750, 300);
    timeText.setCharacterSize(50);
    timeText.setFillColor(sf::Color::Black);

    for (sf::Text &t : time)
    {
        t.setFont(font);
        t.setCharacterSize(50);
        t.setFillColor(sf::Color::Black);
    }

    time[0].setString("1");
    time[1].setString("10");
    time[2].setString("30");

    time[0].setPosition(900, 300);
    time[1].setPosition(950, 300);
    time[2].setPosition(1050, 300);
};

void GameMenu::handleInput(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (singlePlayer.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            // Handle single player button click
            gameRef->createGameBoard(selectedTime, true);
        }
        else if (multiPlayer.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            // Handle multiplayer button click
            gameRef->createGameBoard(selectedTime);
        }
        else if (exit.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            // Handle exit button click
            gameRef->exitGame();
        }
        else if (time[0].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            selectedTime = TimeIndex::One;
        }
        else if (time[1].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            selectedTime = TimeIndex::Ten;
        }
        else if (time[2].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            selectedTime = TimeIndex::Thirty;
        }
    }
}

void GameMenu::update()
{
    for (int i = 0; i < 3; i++)
    {
        if (i == selectedTime)
            time[i].setFillColor(sf::Color::White);
        else
            time[i].setFillColor(sf::Color::Black);
    }
}

void GameMenu::render()
{
    window.draw(backgroundSprite);
    window.draw(title);
    window.draw(singlePlayer);
    window.draw(multiPlayer);
    window.draw(exit);
    window.draw(timeText);
    for (sf::Text &t : time)
    {
        window.draw(t);
    }
}
