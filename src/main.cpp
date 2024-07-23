#include <SFML/Graphics.hpp>
#include <iostream>
#include "utils.hpp"

int gamewidth = sf::VideoMode::getDesktopMode().width;
int gameheight = sf::VideoMode::getDesktopMode().height;

int main()
{
    sf::RenderWindow window(sf::VideoMode(gamewidth, gameheight), "Example Window 1");
    // window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "Font not loaded" << std::endl;
    }

    // initiate time
    sf::Clock clock;
    sf::Clock gametime;

    // Snake object
    sf::CircleShape Snake(10.f, 3);

    Snake.setPosition(gamewidth / 2, gameheight / 2);
    Snake.setOrigin(10, 10);
    Snake.setFillColor(sf::Color::White);
    float directionX = 0, directionY = 0;
    float constRot = -30;
    Snake.setRotation(constRot);
    int length = 1;

    // food object
    sf::CircleShape food(8.f);
    food.setOrigin(8, 8);
    Snake.setFillColor(sf::Color::White);
    food.setPosition(random(gamewidth, gametime.getElapsedTime().asSeconds()), random(gameheight, gametime.getElapsedTime().asSeconds()));

    sf::Text bob;
    while (window.isOpen())
    {

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (std::string(1, static_cast<char>(event.text.unicode)) == "w")
                {
                    directionX = 0;
                    directionY = -1;
                    Snake.setRotation(constRot + 270);
                }
                if (std::string(1, static_cast<char>(event.text.unicode)) == "a")
                {
                    directionX = -1;
                    directionY = 0;
                    Snake.setRotation(constRot + 180);
                }
                if (std::string(1, static_cast<char>(event.text.unicode)) == "s")
                {
                    directionX = 0;
                    directionY = 1;
                    Snake.setRotation(constRot + 90);
                }
                if (std::string(1, static_cast<char>(event.text.unicode)) == "d")
                {
                    directionX = 1;
                    directionY = 0;
                    Snake.setRotation(constRot);
                }
                if (event.text.unicode < 128)
                {
                    std::string str = std::string(1, static_cast<char>(event.text.unicode));
                    std::string characters = "ASCII character typed here ab: " + event.text.unicode;
                    bob.setString(characters);
                    bob.setFont(font);
                    bob.setCharacterSize(24);
                    bob.setFillColor(sf::Color::Red);
                    std::cout << "bob" + str << std::endl;
                }
            }
        }
        sf::FloatRect FoodBound = food.getGlobalBounds();
        sf::FloatRect SnakeBound = Snake.getGlobalBounds();

        if (SnakeBound.intersects(FoodBound))
        {
            length = length + 1;
            food.setPosition(random(gamewidth, gametime.getElapsedTime().asSeconds()), random(gameheight, gametime.getElapsedTime().asSeconds()));
            
        }

        float speed = 100;
        float elapsed = clock.restart().asSeconds();
        Snake.move(elapsed * speed * directionX, elapsed * speed * directionY);

        window.clear();
        window.draw(Snake);
        window.draw(food);
        window.draw(bob);

        window.display();
    }
}
