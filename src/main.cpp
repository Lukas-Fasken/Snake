#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <vector>
#include "utils.hpp"

// int gamewidth = sf::VideoMode::getDesktopMode().width;
int gamewidth = 800;
// int gameheight = sf::VideoMode::getDesktopMode().height;
int gameheight = 600;

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
    size_t length = 0;

    // food object
    sf::CircleShape food(8.f);
    food.setOrigin(8, 8);
    food.setFillColor(sf::Color::Green);
    food.setPosition(random(gamewidth, gametime.getElapsedTime().asSeconds()), random(gameheight, gametime.getElapsedTime().asSeconds()));

    // leader path
    std::deque<sf::Vector2f> path;
    path.push_back(Snake.getOrigin());
    size_t PATH_LENGTH = 0;

    // follower
    std::vector<sf::CircleShape> followers(0, sf::CircleShape(8.f));
    sf::CircleShape follower(8.f);
    follower.setOrigin(8, 8);
    follower.setFillColor(sf::Color::White);
    size_t offset = 1000;

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

        if (path.size() >= PATH_LENGTH)
        {
            path.pop_front();
        }
        path.push_back(Snake.getPosition());

        sf::FloatRect FoodBound = food.getGlobalBounds();
        sf::FloatRect SnakeBound = Snake.getGlobalBounds();

        if (SnakeBound.intersects(FoodBound))
        {
            length = length + 1;
            PATH_LENGTH = (length+1) * offset;
            sf::CircleShape follower(8.f);
            follower.setFillColor(sf::Color::White);
            follower.setOrigin(8, 8);
            followers.push_back(follower);
            food.setPosition(random(gamewidth, gametime.getElapsedTime().asSeconds()), random(gameheight, gametime.getElapsedTime().asSeconds()));
        }

        // follower positioning
        for (size_t i = 0; i < followers.size(); ++i)
        {
            if (path.size() >= (i + 1) * offset)
            {
                followers[i].setPosition(path[(i + 1) * offset]);
            }
            else
            {
                followers[i].setPosition(path[(int)path.size()]);
            }
        }

        float speed = 100;
        float elapsed = clock.restart().asSeconds();
        Snake.move(elapsed * speed * directionX, elapsed * speed * directionY);

        window.clear();
        for (auto &follower : followers)
        {
            window.draw(follower);
        }
        window.draw(Snake);
        window.draw(food);

        window.display();
    }
}
