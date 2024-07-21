#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Example Window 2");
    window.setFramerateLimit(60);
    sf::Font font;
    sf::Text text;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    //font.loadFromFile("arial.ttf");
    
    
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    
                    text.setFont(font);
                    
                    //std::string characters= "ASCII character typed: " + static_cast<char>(event.text.unicode);
                    std::string characters= "ASCII character typed here ab: " + std::string(1,static_cast<char>(event.text.unicode));
                    text.setString(characters);
                    text.setCharacterSize(24);
                    text.setFillColor(sf::Color::Red);
                    text.setPosition(100.f, 500.f);
                    std::cout << "bob" << std::endl;
                }
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }
}
