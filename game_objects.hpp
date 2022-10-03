#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>
#include <iostream>
//#include <stdexcept>
//#include <cstring>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

// This enum help us identify textures in the vector container
enum textures_posiions
{
    BLOCK = 0,
    BALL,
    PADDLE,
    BACKGROUD,

    TEXTURES_COUNT
};

enum block_textures
{
    BLUE = 0,
    SALAD = 2,
    PURPLE = 4,
    RED = 6,
    ORANGE = 8,
    SKY = 10,
    YELLOW = 12,
    GREEN = 14,
    GRAY = 16,
    BROWN = 18,

    BLK_T_COUNT = 20 //10
};

enum ability_textures
{
    PLUS_50 = 0,
    PLUS_100_1,
    PLUS_100_2,
    PLUS_100_3,
    PLUS_100_4,
    PLUS_100_5,
    PLUS_100_6,
    PLUS_250,
    PLUS_500,
    SLOW,
    FAST,
    THREE_BALLS,
    RED_FIRE,
    GREEN_FIRE,
    MAKE_TINY,
    MAKE_WIDE,
    WITH_TOKEN,
    EMPTY,

    ABILITY_COUNT //18
};

enum paddle_textures
{
    CAPSULE_1 = 0,
    CAPSULE_2,
    CAPSULE_3,
    CONNECTOR_1,
    CONNECTOR_2,
    CONNECTOR_3,
    WIDE,
    TINY,

    PADDLE_COUNT //8
};

enum ball_textures
{
    SMALL = 0,
    MEDIUM,
    LARGE,
    EXTRA_LARGE,

    BALL_COUNT //4
};

enum specials
{
    STAR = 0,
    HEART,
    TOKEN,
    BACKGROUND,

    SPECIALS_COUNT //3
};

class GameObjects
{
    public:
        GameObjects() = delete;
        //GameObjects(const int& qty) : quantity(qty)
        //{
        //    textures.resize(quantity);
        //    sprites.resize(quantity);
        //    blocks.resize(20);
        //}

        GameObjects(const int& blocks_qty) : blocks_quantity(blocks_qty)
        {
            //Resize container with blocks
            blocks.resize(blocks_quantity);
            //Rrsize container with textures for blocks
            blocks_texture.resize(BLK_T_COUNT);

            //Initialize textures for the blocks
            for (int index{}; index < BLK_T_COUNT; index++ )
            {
                parse_texture(blocks_texture.at(index), index + 1);
            }

            int dummy_texture_test{};
            //Initialize sprites of the blocks
            for (auto& block: blocks)
            {
                set_texture(block, dummy_texture_test++);
            }

            //Rrsize container with textures for abilities
            abilities_texture.resize(ABILITY_COUNT);
            int dummy_parser{31};
            //Initialize textures for the paddle
            for (int index{}; index < ABILITY_COUNT; index++)
            {
                if (index == 7)
                    dummy_parser++;

                parse_texture(abilities_texture.at(index), index + dummy_parser);
            }

        }

        struct parameters
        {
            sf::Sprite sprite;
            sf::Vector2f position;
            float pos_x{}, pos_y{}, speed_x{}, speed_y{}, acc_x{}, acc_y{};

        };

        //safe parsing texture method
        void parse_texture(sf::Texture& item, const int& number_in_dir) noexcept;
        //set texture for the given sprite in the parameters
        void set_texture(parameters& item, const int& texture) noexcept;
        //set position of the given item
        void set_position(parameters& item, const float& loc_X, const float& loc_Y) noexcept;
        //resize sprite
        void resize_sprite(parameters& item, const sf::Vector2f& scale) noexcept;

        //Draw method
        void draw_object(sf::RenderWindow& wind, const parameters& item);

    public:
        //Tells how there many there different type of objects
        //int quantity{};
        int blocks_quantity;

        //=___=BLOCKS=___=
        std::vector<parameters> blocks;
        std::vector<sf::Texture> blocks_texture;

        //=___=SQUARES=___=
        std::vector<parameters> squares;
        std::vector<sf::Texture> squares_texture;

        //=___=ABILITIES=___=
        std::vector<parameters> abilities;
        std::vector<sf::Texture> abilities_texture;

        //=___=PADDLE=___=
        parameters paddle;
        std::vector<sf::Texture> paddle_texture;

        //=___=SPECIALS=___=
        std::vector<parameters> specials;
        std::vector<sf::Texture> specials_texture;

        //! terrible path specification HERE:
        const std::string abs_path_begin {"D:/CPP/breakout/arkanoid/data/textures/"};
        const std::string abs_path_end {"-Breakout-Tiles.png"};
        const std::string template_message{ " <--- Can't find texture source file in this location..." };
};

//method: parsing texture from file to the element of the container
inline void GameObjects::parse_texture(sf::Texture& item, const int& number_in_dir) noexcept
{
    bool parsing_status{};
    
    std::string texture_number = std::to_string(number_in_dir);
    if (number_in_dir < 10) texture_number.insert(0, "0");
    std::string path = abs_path_begin + texture_number + abs_path_end;

    parsing_status = item.loadFromFile(path);
    try
    {
        if (!parsing_status)
        {
            path += template_message;
            throw std::exception(path.c_str());
        }
        else
            std::cout << "By address captured texture: " << path << '\n';
    }
    catch (const std::exception& inside_function)
    {
        std::cout << inside_function.what();
    }

    //Smoothing a texture makes pixel boundaries less visible (but the image a little more blurry),
    //which can be desirable if it is up-scaled.
    item.setSmooth(true);
}

//method: initialize sprite by texture
inline void GameObjects::set_texture(parameters& item, const int& texture) noexcept
{
    item.sprite.setTexture(blocks_texture.at(texture));
}

//method: set position of the sprite
inline void GameObjects::set_position(parameters& item, const float& loc_X, const float& loc_Y) noexcept
{
    
    item.position = sf::Vector2(loc_X, loc_Y);
    item.sprite.setPosition(item.position);
}

inline void GameObjects::resize_sprite(parameters& item, const sf::Vector2f& scale) noexcept
{
    item.sprite.setScale(scale);
}

inline void GameObjects::draw_object(sf::RenderWindow& wind, const parameters& item)
{
    wind.draw(item.sprite);
}

