#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> PHYSICS CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

// C++ headers

// API

// SFML headers

// Custom headers
// #include "util.hpp"
// #include "game_page.hpp"
// #include "game_page_statics.hpp"
#include "game_page_dynamics.hpp"
// #include "game_page_process.hpp"

// DEFINES

inline static void recalculate1DKinematics(std::vector<float>& unit, const float& d_t)
{
	// #2____________________________________________________________________________
	//
	// Friction between paddle and the surface will cause loss of acceleration

	unit.at(A_X) -= unit.at(V_X) * Game::DynamicUnits::pdl_friction;

	// #3____________________________________________________________________________
	//
	// Increment/Decriment in the X axis calculated in the classical way

	unit.at(DELTA_X) = unit.at(V_X) * d_t + unit.at(A_X) * d_t * d_t / 2.f;

	// #4____________________________________________________________________________
	//
	// NOTE: That only now we can update speed for the next iteration
	// OTHERWISE algorithm doesn't make any sense

	unit.at(V_X) += unit.at(A_X) * d_t;
}

inline static void recalculate2DKinematics(std::vector<float>& unit, const float& d_t)
{
	// #2____________________________________________________________________________
	//
	// Friction between paddle and the surface will cause loss of acceleration

	unit.at(A_X) -= unit.at(V_X) * Game::DynamicUnits::bll_friction;
	unit.at(A_Y) -= unit.at(V_Y) * Game::DynamicUnits::bll_friction;

	// #3____________________________________________________________________________
	//
	// Increment/Decriment in the X axis calculated in the classical way

	unit.at(DELTA_X) = unit.at(V_X) * d_t + unit.at(A_X) * d_t * d_t / 2.f;
	unit.at(DELTA_Y) = unit.at(V_Y) * d_t + unit.at(A_Y) * d_t * d_t / 2.f;

	// Simplified version of the main equation for the coordinate
	// unit.at(DELTA_X) = unit.at(V_X) * d_t;
	// unit.at(DELTA_Y) = unit.at(V_Y) * d_t;

	// #4____________________________________________________________________________
	//
	// NOTE: That only now we can update speed for the next iteration
	// OTHERWISE algorithm doesn't make any sense

	unit.at(V_X) += unit.at(A_X) * d_t;
	unit.at(V_Y) += unit.at(A_Y) * d_t;

	// After this equations - ball will loose speed

	// #5____________________________________________________________________________
	//
	// So we have to speed up it

	// Thru X axis
	if ((unit.at(V_X) < Game::DynamicUnits::bll_V_step) && (unit.at(V_X) > 0))
	{
		unit.at(V_X) = Game::DynamicUnits::bll_V_step;
	}
	else if ((std::abs(unit.at(V_X)) < Game::DynamicUnits::bll_V_step) && (unit.at(V_X) < 0))
	{
		unit.at(V_X) = -Game::DynamicUnits::bll_V_step;
	}

	// Thru Y axis
	if ((unit.at(V_Y) < Game::DynamicUnits::bll_V_step) && (unit.at(V_Y) > 0))
	{
		unit.at(V_Y) = Game::DynamicUnits::bll_V_step;
	}
	else if ((std::abs(unit.at(V_Y)) < Game::DynamicUnits::bll_V_step) && (unit.at(V_Y) < 0))
	{
		unit.at(V_Y) = -Game::DynamicUnits::bll_V_step;
	}
}

inline static void recalculateAblKinematics(std::vector<float>& unit, const float& d_t)
{
	// unit.at(V_Y) = Game::DynamicUnits::abl_V_step;

	// #2____________________________________________________________________________
	//
	// Friction between paddle and the surface will cause loss of acceleration

	unit.at(A_X) -= unit.at(V_X) * Game::DynamicUnits::abl_friction;
	unit.at(A_Y) -= unit.at(V_Y) * Game::DynamicUnits::abl_friction;

	// #3____________________________________________________________________________
	//
	// Increment/Decriment in the X axis calculated in the classical way

	unit.at(DELTA_X) = unit.at(V_X) * d_t + unit.at(A_X) * d_t * d_t / 2.f;
	unit.at(DELTA_Y) = unit.at(V_Y) * d_t + unit.at(A_Y) * d_t * d_t / 2.f;

	// #4____________________________________________________________________________
	//
	// NOTE: That only now we can update speed for the next iteration
	// OTHERWISE algorithm doesn't make any sense

	unit.at(V_X) += unit.at(A_X) * d_t;
	unit.at(V_Y) += unit.at(A_Y) * d_t;

	// After this equations - ball will loose speed

	// #5____________________________________________________________________________
	//
	// So we have to speed up it

	// Thru X axis
	// if (
	//		( std::abs(unit.at(V_X)) < Game::DynamicUnits::abl_V_step )
	//		&&
	//		( unit.at(DELTA_X) >= Default::block_height )
	//	)
	//{
	//	unit.at(V_X) = ( (unit.at(V_X) > 0)? 1: -1 ) * Game::DynamicUnits::abl_V_step;
	// }

	// Thru Y axis
	// if (
	//	(std::abs(unit.at(V_Y)) < Game::DynamicUnits::abl_V_step)
	//	&&
	//	(unit.at(DELTA_Y) >= Default::block_height)
	//	)
	//{
	//	unit.at(V_Y) = ((unit.at(V_Y) > 0) ? 1 : -1) * Game::DynamicUnits::abl_V_step;
	// }
}

inline static void simulatePhysics(const float& d_time)
{
	// #1____________________________________________________________________________
	//
	// First of all we need to caut inertia of the paddle
	// according to the last frame data

	// PADDLE
	pdl(A_X) = 0;

	// BALL
	bll(A_X) = 0;
	bll(A_Y) = 0;

	// #?____________________________________________________________________________

	// while (window.pollEvent(Game::Process::event))
	//{

	//	if (Game::Process::event.type == sf::Event::KeyPressed)
	//	{
	//					//Also close by 'Esc' keyboard button
	//		if (Game::Process::event.key.code == sf::Keyboard::Escape)
	//		{
	//			Game::Process::running = false;  // also should be here
	//			window.close();
	//			break;
	//		}

	//		//paddle(A_X) = 0;

	//		//LEFT button we use for loosing speed in the X axis
	//		else if (Game::Process::event.key.code == sf::Keyboard::Left)
	//		{
	//			//paddle(V_X) = -Game::DynamicUnits::pdl_V_step;
	//			paddle(A_X) -= Game::DynamicUnits::pdl_A_step;
	//		}
	//		//RIGHT button we use for increasing speed in the X axis
	//		else if (Game::Process::event.key.code == sf::Keyboard::Right)
	//		{
	//			//paddle(V_X) = Game::DynamicUnits::pdl_V_step;
	//			paddle(A_X) += Game::DynamicUnits::pdl_A_step;
	//		}
	//	}
	//}

	// #2____________________________________________________________________________
	//
	// Friction between paddle and the surface will cause loss of acceleration

	// PADDLE
	// paddle(A_X) -= paddle(V_X) * Game::DynamicUnits::pdl_friction;

	////BALL
	/////<<<---It can be improoved
	// ball(A_X) -= ball(V_X) * Game::DynamicUnits::bll_friction;
	// ball(A_Y) -= ball(V_Y) * Game::DynamicUnits::bll_friction;
	/////<<<---It can be improoved

	////#3____________________________________________________________________________
	////
	////Increment/Decriment in the X axis calculated in the classical way

	////PADDLE
	// paddle(DELTA_X) = paddle(V_X) * d_time + paddle(A_X) * d_time * d_time / 2.f;

	////BALL
	////Simplified version of the main equation for the coordinate
	/////<<<---It can be improoved
	// ball(DELTA_X) = ball(V_X) * d_time + ball(A_X) * d_time * d_time / 2.f;
	// ball(DELTA_Y) = ball(V_Y) * d_time + ball(A_Y) * d_time * d_time / 2.f;
	////ball(DELTA_X) = ball(V_X) * d_time;
	////ball(DELTA_Y) = ball(V_Y) * d_time;
	/////<<<---It can be improoved

	////#4____________________________________________________________________________
	////
	////NOTE: That only now we can update speed for the next iteration
	////OTHERWISE algorithm doesn't make any sense

	////PADDLE
	// paddle(V_X) += paddle(A_X) * d_time;
	//
	////BALL
	/////<<<---It can be improoved
	////ball(V_X) += ball(A_X) * d_time;
	////ball(V_Y) += ball(A_Y) * d_time;
	/////<<<---It can be improoved

	recalculate1DKinematics(Game::DynamicUnits::paddle_kinematics, d_time);

	recalculate2DKinematics(Game::DynamicUnits::ball_kinematics, d_time);

	for (auto& ability : Game::DynamicUnits::conveyor_map)
	{
		if (ability.block) continue;

		ability.kinematics.at(A_X) = 0;
		ability.kinematics.at(A_Y) = 0;

		recalculateAblKinematics(ability.kinematics, d_time);
	}

	// That is pretty much all physics that we have
}
