#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "game_objects.hpp"


unsigned int initWindWidth{ 1200 };
unsigned int initWindHeight{ 1900 };

float scale_on_risize_X{};
float scale_on_risize_Y{};

//int WinMain()
int main()
{
    //=====Opening screen parameters=====

    //Get user screen properties
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    //Specify opening screen ratio
    sf::Vector2u screen_s(initWindHeight, initWindWidth);
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
    dwgs_access->abilities.at(0).sprite.setPosition(sf::Vector2f(5.f*x_step, 3.f*y_step));
    //set defaulted texture
    dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(EMPTY));
    //resize
    dwgs_access->resize_sprite(dwgs_access->abilities.at(0), sf::Vector2f(.393f, .5f));
    

    //TESTED BLOCK
    dwgs_access->set_position(dwgs_access->blocks.at(3 + 3 * 5), x + static_cast<float>(3+3) * x_step, y + static_cast<float>(3) * y_step);
    dwgs_access->set_position(dwgs_access->blocks.at(4 + 2 * 5), x + static_cast<float>(4+1) * x_step, y + static_cast<float>(2) * y_step);
        
    //TESTED BALL

    //set ball in the specific location
    dwgs_access->ball.sprite.setPosition(sf::Vector2f(7.f * x_step, 6.f * y_step));
    //set defaulted texture
    dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(SMALL), true);
    //resize
    //dwgs_access->resize_sprite(dwgs_access->ball, sf::Vector2f(.393f, .5f));

    //TESTED PADDLE

    //set paddle in the specific location
    dwgs_access->paddle.sprite.setPosition(sf::Vector2f(3.f * x_step, 9.f * y_step));
    //set defaulted texture
    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(TINY), true);
    //resize
    dwgs_access->resize_sprite(dwgs_access->paddle, sf::Vector2f(.25f, .25f));


    //==========GAME LOOP==========

    //create an event
    sf::Event game_event{};//!! Usually this line inside game loop, don't see much necassity

    //create loop
    while(window.isOpen())
    {
        //RESIZE sprites when window have resized
        /*
        This will update the render area to the dimensions of the window every
        time the window is resized rather than scaling the render area to fit the window.
        */
        if (game_event.type == sf::Event::Resized)
        {
            sf::Vector2f origin(0, 0);
            sf::Vector2f new_size(static_cast<float>(game_event.size.width), static_cast<float>(game_event.size.height));

            sf::FloatRect resized_view(origin, new_size);
            window.setView(sf::View(resized_view));
        }


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
                //CHANGE ABILITIES
                
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

                //CHANGE BALLS
                else if (game_event.key.code == sf::Keyboard::U)
                    dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(SMALL), true);
                else if (game_event.key.code == sf::Keyboard::I)
                    dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(MEDIUM), true);
                else if (game_event.key.code == sf::Keyboard::O)
                    dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(LARGE), true);
                else if (game_event.key.code == sf::Keyboard::P)
                    dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(EXTRA_LARGE), true);

                //CHANGE PADDLES
                else if (game_event.key.code == sf::Keyboard::Num1)
                    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CAPSULE_1), true);
                else if (game_event.key.code == sf::Keyboard::Num2)
                    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CAPSULE_2), true);
                else if (game_event.key.code == sf::Keyboard::Num3)
                    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CAPSULE_3), true);
                else if (game_event.key.code == sf::Keyboard::Num4)
                    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CONNECTOR_1), true);
                else if (game_event.key.code == sf::Keyboard::Num5)
                    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CONNECTOR_2), true);
                else if (game_event.key.code == sf::Keyboard::Num6)
                    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CONNECTOR_3), true);
                else if (game_event.key.code == sf::Keyboard::Num7)
                    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(WIDE), true);
                else if (game_event.key.code == sf::Keyboard::Num8)
                    dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(TINY), true);

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

        //Draw ABILITIES
        dwgs_access->draw_object(window, dwgs_access->abilities.at(0));

        //Draw BALL
        dwgs_access->draw_object(window, dwgs_access->ball);

        //Draw PADDLE
        dwgs_access->draw_object(window, dwgs_access->paddle);

        //Display everything to the screen
        window.display();
    }
    
    return 0;
}