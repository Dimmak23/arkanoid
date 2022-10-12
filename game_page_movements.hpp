#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> MOVEMENTS CODE UNITS		//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers


//API


//SFML headers

//Custom headers
//#include "util.hpp"
//#include "game_page.hpp"
//#include "game_page_statics.hpp"
#include "game_page_dynamics.hpp"
//#include "game_page_process.hpp"

#define paddle(lvalue) Game::dynamicUnits::paddle_kinematics.at(lvalue)
#define ball(lvalue) Game::dynamicUnits::ball_kinematics.at(lvalue)

static void moveUnits(Game::dynamicUnits& dynamics)
{
	//It is a '0' by Y axis and anything that by X axis, that we got in the kinematics container
	dynamics.paddle->move(sf::Vector2f(paddle(DELTA_X), 0));

	//Take deltas from kinematic container and move the ball
	dynamics.ball->move(sf::Vector2f(ball(DELTA_X), ball(DELTA_Y)));


}
