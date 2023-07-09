#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>


int init_window();
class Board{
    private:
    sf :: RenderWindow mwindow;
    sf :: RectangleShape wtiles;
    sf :: RectangleShape btiles;
    public:
    Board();
    void Chess_Board();

};