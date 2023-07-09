#include "window.hpp"
Board::Board()
:mwindow(sf::VideoMode(1080, 1080), "SFML works!"),

wtiles(){
    wtiles.setSize(sf::Vector2f(120, 50));
    wtiles.setFillColor(sf::Color::White);
};
btiles(){
    btiles.setSize(sf::Vector2f(120, 50));
    btiles.setFillColor(sf::Color::Black);
}

void Board:: init_window(){
     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Chess_Board() ;       
        draw();
        display();
    }

}
void Board::Chess_Board(){
    for(int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            bool isLightSquare=(i+j)%2!=0;
            int squareColour =(isLightSquare)?btiles:wtiles:
            int position =new Vector(120+i,50+j);
            
        }
    }

}

























// #include <SFML/Graphics.hpp>

// int init_window()
// {
//     sf::RenderWindow window(sf::VideoMode(1080, 1080), "SFML works!");
//     sf::RectangleShape rectangle(sf::Vector2f(128.0f,128.0f));

//     

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.draw(rectangle);
//         window.display();
//     }

//     return 0;
// }
