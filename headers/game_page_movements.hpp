#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> MOVEMENTS CODE UNITS		//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

// C++ headers

// API

// SFML headers

// * Custom
#include "game_page_dynamics.hpp"

static void moveUnits(Game::DynamicUnits& dynamics)
{
	// It is a '0' by Y axis and anything that by X axis, that we got in the kinematics container
	dynamics.paddle->move(sf::Vector2f(pdl(DELTA_X), 0));

	// Take deltas from kinematic container and move the ball
	dynamics.ball->move(sf::Vector2f(bll(DELTA_X), bll(DELTA_Y)));

	// Take deltas from abilities kinematics and throw them
	int index{};
	for (auto& ability : Game::DynamicUnits::conveyor_map)
	{
		if (ability.block)
		{
			index++;
			continue;
		}

		dynamics.conveyor.at(index).move(sf::Vector2f(ability.kinematics.at(DELTA_X), ability.kinematics.at(DELTA_Y)));
		index++;
	}
}
