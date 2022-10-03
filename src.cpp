#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <compare>
#include <iostream>

int WinMain()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u screen_s(static_cast<unsigned int>(200), static_cast<unsigned int>(200));
    
    sf::RenderWindow window(sf::VideoMode(screen_s, desktop.bitsPerPixel), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}