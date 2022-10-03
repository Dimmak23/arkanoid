#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "game_objects.hpp"

//int WinMain()
int main()
{
    //=====Opening screen parameters=====

    //Get user screen properties
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    //Specify opening screen ratio
    sf::Vector2u screen_s(static_cast<unsigned int>(1900), static_cast<unsigned int>(1200));
    //desktop.bitsPerPixel --> gets depth of user screen (bits in pixels)
    sf::RenderWindow window(sf::VideoMode(screen_s, desktop.bitsPerPixel), "Arkanoid, produced by DimmaK (c)");
    window.setFramerateLimit(120);//!not sure if any reason in this line

    //=====Render sprites=====

    //Initialize a pointer to game objects
    std::unique_ptr<GameObjects> dwgs_access = std::make_unique<GameObjects>(20);


    //=====TEST_BLOCKS=====
    float x{ 0.f };
    float y{ 0.f };

    const float x_step = 192.25f;
    const float y_step = 64.25f;

    float pos_x{};
    float pos_y{};

    for (int row{}; row < 4; row++)
        for (int column{}; column < 5; column++)
        {
            pos_x = x + static_cast<float>(column) * x_step;
            pos_y = y + static_cast<float>(row) * y_step;
            dwgs_access->set_position(dwgs_access->blocks.at(column + row * 5), x + static_cast<float>(column) * x_step, y + static_cast<float>(row) * y_step);
            std::cout << "Send to screen: [row=" << row << ", column=" << column << ", pos_x=" << pos_x << ", pos_y=" << pos_y << "].\n";
        }

    //=====TEST_ABILITIES=====

    //set 1 for now
    dwgs_access->abilities.resize(1);
    //set in the specific location
    dwgs_access->abilities.at(0).sprite.setPosition(sf::Vector2f(200.f, 350.f));
    //set defaulted texture
    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(EMPTY));
    //resize
    dwgs_access->resize_sprite(dwgs_access->abilities.at(0), sf::Vector2f(.5f, .5f));
    
        
    //=====Game loop=====

    //create an event
    sf::Event game_event{};//!! Usually this line inside game loop, don't see much necassity

    //create loop
    while(window.isOpen())
    {

        // check the type of the event...
        while (window.pollEvent(game_event))
        {
            // window closed
            if(game_event.type == sf::Event::Closed)
            {
                window.close();
                break;            
            }

            // key pressed
            else if (game_event.type == sf::Event::KeyPressed)
            {
                if (game_event.key.code == sf::Keyboard::A)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_50));
                else if (game_event.key.code == sf::Keyboard::S)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_1));
                else if (game_event.key.code == sf::Keyboard::D)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_2));
                else if (game_event.key.code == sf::Keyboard::F)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_3));
                else if (game_event.key.code == sf::Keyboard::G)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_4));
                else if (game_event.key.code == sf::Keyboard::H)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_5));
                else if (game_event.key.code == sf::Keyboard::J)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_6));
                else if (game_event.key.code == sf::Keyboard::K)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_250));
                else if (game_event.key.code == sf::Keyboard::L)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_500));
                else if (game_event.key.code == sf::Keyboard::X)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(SLOW));
                else if (game_event.key.code == sf::Keyboard::C)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(FAST));
                else if (game_event.key.code == sf::Keyboard::V)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(THREE_BALLS));
                else if (game_event.key.code == sf::Keyboard::B)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(RED_FIRE));
                else if (game_event.key.code == sf::Keyboard::N)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(GREEN_FIRE));
                else if (game_event.key.code == sf::Keyboard::M)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(MAKE_TINY));
                else if (game_event.key.code == sf::Keyboard::Q)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(MAKE_WIDE));
                else if (game_event.key.code == sf::Keyboard::W)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(WITH_TOKEN));
                else if (game_event.key.code == sf::Keyboard::E)
                    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(EMPTY));
            }


            // we don't process other types of events
            else
                break;
        }

        //Clear screen
        window.clear();

        //Draw BLOCKS
        for (auto& block : dwgs_access->blocks)
        {
            dwgs_access->resize_sprite(block, sf::Vector2f(0.5f, 0.5f));
            dwgs_access->draw_object(window, block);
        }

        //Draw abilities
        dwgs_access->draw_object(window, dwgs_access->abilities.at(0));

        //Display everything to the screen
        window.display();
    }
    
    return 0;
}