#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> PHYSICS CODE UNITS			//
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


//DEFINES
//It seems that here construction paddle_kinematics.at(L_VALUE) are spreading a lot,
//so why not simpliy this moment

#define paddle(lvalue) Game::dynamicUnits::paddle_kinematics.at(lvalue)


inline static void simulatePhysics(const float& d_time)
{
	//#1____________________________________________________________________________
	// 
	//First of all we need to caut inertia of the paddle
	//according to the last frame data

	paddle(A_X) = 0;

	//#2____________________________________________________________________________
	//
	//Friction between paddle and the surface will cause loss of acceleration
	
	paddle(A_X) -= paddle(V_X) * Game::dynamicUnits::pdl_friction;

	//#3____________________________________________________________________________
	//
	//Increment/Decriment in the X axis calculated in the classical way

	paddle(DELTA_X) = paddle(V_X) * d_time + paddle(A_X) * d_time * d_time / 2.f;

	//#4____________________________________________________________________________
	//
	//NOTE: That only now we can update speed for the next iteration
	//OTHERWISE algorithm doesn't make any sense
	paddle(V_X) += paddle(A_X) * d_time;



	//That is pretty much all physics that we have

}
