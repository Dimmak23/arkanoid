#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//				THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME CODE UNITS				//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//* C++ std
#include <algorithm>
#include <iterator>
#include <ranges>
#include <string>
#include <vector>

//* SFML
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

//* Custom
#include "util.hpp"

// dependable headers with some class definitions
#include "game_page_dynamics.hpp"
#include "game_page_statics.hpp"

// DEFINES
// It seems that here construction paddle_kinematics.at(L_VALUE) and ball_kinematics.at(L_VALUE) are spreading a lot,
// so why not simpliy this moment
#define pdl(lvalue) Game::DynamicUnits::paddle_kinematics.at(lvalue)
#define bll(lvalue) Game::DynamicUnits::ball_kinematics.at(lvalue)

// First Game namespace declaration
namespace Game
{
	class StaticUnits;
	class DynamicUnits;
	class Process;

	static void initialize_frame(sf::RectangleShape& rect, const float& size_x, const float& size_y,
								 const sf::Color& border_color,	   // Black, White, Red, Green, Blue, Yellow, Magenta,
																   // Cyan, Transparent
								 const sf::Color& fill_color,	   // Black, White, Red, Green, Blue, Yellow, Magenta,
																   // Cyan, Transparent
								 const float& thikness, const float& pos_x, const float& pos_y) noexcept;

};	  // namespace Game

void Game::initialize_frame(sf::RectangleShape& rect, const float& size_x, const float& size_y,
							const sf::Color& border_color,	  // Black, White, Red, Green, Blue, Yellow, Magenta, Cyan,
															  // Transparent
							const sf::Color& fill_color,	  // Black, White, Red, Green, Blue, Yellow, Magenta, Cyan,
															  // Transparent
							const float& thikness, const float& pos_x, const float& pos_y) noexcept
{
	rect.setSize(sf::Vector2f(size_x, size_y));	   // Size it
	rect.setOutlineColor(border_color);			   // Color it border
	rect.setFillColor(fill_color);				   // Color background
	rect.setOutlineThickness(thikness);			   // Set thikness, -<value>: outline inside, +<value>: outline outside
	rect.setPosition(sf::Vector2f(pos_x, pos_y));
}
