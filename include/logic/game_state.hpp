#pragma once
#include <SFML/Graphics.hpp>

class GameState {
public:
  virtual ~GameState() {}

  virtual void init() = 0;
  virtual void handleInput(sf::Event &event) = 0;
  virtual void update() = 0;
  virtual void render() = 0;
};