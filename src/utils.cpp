#include <iostream>
#include "utils.hpp"


int random(int max, float seed){
    srand (time(NULL)*((int)seed+1));
    int num=rand() % max;
    return num;
    
}

sf::RectangleShape convertToRectangleShape(sf::FloatRect& rect) {
    sf::RectangleShape rectangle;
    rectangle.setPosition(rect.left, rect.top);
    rectangle.setSize(sf::Vector2f(rect.width, rect.height));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color::Blue);
    return rectangle;
}

// class object{
//     private:
//     sf::CircleShape follower(float x=8);
//     public:
//     int posX;
//     int posY;
//     object(int posX, int posY){
//         this->posX=posX;
//         this->posY=posY;
//     }
// };

/*
sf::Text write(sf::String& input, int posX, int posY, int size, sf::Color& color){
    sf::Font font;
    sf::Text text;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "Font not loaded" << std::endl;
    }
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(size);
    text.setPosition(posX,posY);
    text.setFillColor(color);

    return text;
}
*/


/*
class Tekst{
    public:
    sf::String write;
    int size;
    int posX;
    int posY;
    Tekst(sf::String write, int size, int posX, int posY){
        this->write=write;
        this->size=size;
        this->posX=posX;
        this->posY=posY;

    }
};

*/