#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> COLLISIONS CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers


//API


//SFML headers

//Custom headers
//#include "util.hpp"
#include "game_page.hpp"
//#include "game_page_statics.hpp"
#include "game_page_dynamics.hpp"
//#include "game_page_process.hpp"



#define paddle(lvalue) Game::dynamicUnits::paddle_kinematics.at(lvalue)
#define ball(lvalue) Game::dynamicUnits::ball_kinematics.at(lvalue)

inline static void collideUnits(Game::dynamicUnits& dynamics, const float& d_time)
{

///////////////////////////////////////PADDLE TO WALL////////////////////////////////////////////

	//SLOWDOWN near the LEFT border line
	if (
		(dynamics.paddle->getGlobalBounds().left < game_field.origin_x + 20.f)  //15.f pixels near the border is a SLOWDOWN ZONE
		&&
		(dynamics.paddle_kinematics.at(V_X) < 0)  //ONLY IF we going to the border, and NOT out from the border
		)
	{
		paddle(V_X) /= 100;
		paddle(A_X) /= 10000;
	}

	//Let's check are we are hitting the LEFT wall by paddle?
	if ( dynamics.paddle->getGlobalBounds().left <= game_field.origin_x )
	{
		dynamics.paddle->setPosition(
							sf::Vector2f(
													game_field.origin_x + dynamics.paddle->getGlobalBounds().width/2,
													to_f(game_field.origin_y + game_field.overall_height - Default::block_height)
												)
		);

		paddle(A_X) *= -1.f;
		paddle(V_X) *= Game::dynamicUnits::pdl_bounce;
		//dynamics.paddle_kinematics.at(DELTA_X) += 5.f;
		paddle(DELTA_X) = paddle(V_X) * d_time + paddle(A_X) * d_time * d_time / 2.f;

	}

	//SLOWDOWN near the RIGHT border line
	if (
		( (dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width) > (game_field.origin_x + game_field.overall_width - 20.f) )
		&&
		(dynamics.paddle_kinematics.at(V_X) > 0.1f)  //ONLY IF we going to the border, and NOT out from the border
		)
	{
		paddle(V_X) /= 100;
		paddle(A_X) /= 10000;
	}

	//Let's check are we are hitting the RIGHT wall by paddle?
	if ( (dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width) >= (game_field.origin_x + game_field.overall_width) )
	{
		dynamics.paddle->setPosition(
								sf::Vector2f(
														game_field.origin_x + game_field.overall_width - dynamics.paddle->getGlobalBounds().width / 2,
														to_f(game_field.origin_y + game_field.overall_height - Default::block_height)
													)
		);

		paddle(A_X) *= -1.f;
		paddle(V_X) *= Game::dynamicUnits::pdl_bounce;
		//dynamics.paddle_kinematics.at(DELTA_X) += 5.f;
		paddle(DELTA_X) = paddle(V_X) * d_time + paddle(A_X) * d_time * d_time / 2.f;

	}

///////////////////////////////////////BALL TO WALL////////////////////////////////////////////

	//Let's check are ball hitting the LEFT wall?
	if (dynamics.ball->getGlobalBounds().left <= game_field.origin_x)
	{
		dynamics.ball->setPosition(
									sf::Vector2f(
													game_field.origin_x + dynamics.ball->getGlobalBounds().width / 2,
													dynamics.ball->getPosition().y
											)
		);

		//X axis acceleration will be inverted
		ball(A_X) *= -1.f;

		//Bouncing from the wall
		ball(V_X) *= -Game::dynamicUnits::bll_bounce;
		ball(V_Y) *= Game::dynamicUnits::bll_bounce;

		//coordinates re-calculation
		ball(DELTA_X) = ball(V_X) * d_time + ball(A_X) * d_time * d_time / 2.f;
		ball(DELTA_Y) = ball(V_Y) * d_time + ball(A_Y) * d_time * d_time / 2.f;

	}

	//Let's check are ball hitting the RIGHT wall?
	if ( ( dynamics.ball->getGlobalBounds().left + dynamics.ball->getGlobalBounds().width ) >= ( game_field.origin_x + game_field.overall_width ) )
	{
		dynamics.ball->setPosition(
									sf::Vector2f(
													game_field.origin_x + game_field.overall_width - dynamics.ball->getGlobalBounds().width / 2,
													dynamics.ball->getPosition().y
												)
		);

		//X axis acceleration will be inverted
		ball(A_X) *= -1.f;

		//Bouncing from the wall
		ball(V_X) *= -Game::dynamicUnits::bll_bounce;
		ball(V_Y) *= Game::dynamicUnits::bll_bounce;

		//coordinates re-calculation
		ball(DELTA_X) = ball(V_X) * d_time + ball(A_X) * d_time * d_time / 2.f;
		ball(DELTA_Y) = ball(V_Y) * d_time + ball(A_Y) * d_time * d_time / 2.f;

	}

	//Let's check are ball hitting the CEILING?
	if ( dynamics.ball->getGlobalBounds().top <= game_field.origin_y )
	{
		dynamics.ball->setPosition(
									sf::Vector2f(
													dynamics.ball->getPosition().x,
													game_field.origin_y + dynamics.ball->getGlobalBounds().height / 2
												)
		);

		//Y axis acceleration will be inverted
		ball(A_Y) *= -1.f;

		//Bouncing from the wall
		ball(V_X) *= Game::dynamicUnits::bll_bounce;
		ball(V_Y) *= -Game::dynamicUnits::bll_bounce;

		//coordinates re-calculation
		ball(DELTA_X) = ball(V_X) * d_time + ball(A_X) * d_time * d_time / 2.f;
		ball(DELTA_Y) = ball(V_Y) * d_time + ball(A_Y) * d_time * d_time / 2.f;

	}

///////////////////////////////////////LOST BALL////////////////////////////////////////////

	//Let's check are ball lost?
	if ( ( dynamics.ball->getGlobalBounds().top ) >= ( game_field.origin_y + game_field.overall_height + 10.f ) )  //10.f??? removing GLITCH
	{
		//Decrement lifes
		if(!Game::dynamicUnits::lost_ball) Game::dynamicUnits::lifes -= 1;

		//Set lost ball status for new ball await
		Game::dynamicUnits::lost_ball = true;

	}

/////////////////////////////////////BALL VS PADDLE//////////////////////////////////////////

	//FROM THE TOP OF THE PADDLE
	if  ( 
		( (dynamics.ball->getGlobalBounds().top + dynamics.ball->getGlobalBounds().height) >= dynamics.paddle->getGlobalBounds().top )
		&&
		( dynamics.ball->getGlobalBounds().left >= dynamics.paddle->getGlobalBounds().left )
		&&
		( (dynamics.ball->getGlobalBounds().left + dynamics.ball->getGlobalBounds().width) <= (dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width) )
		&&
		!Game::dynamicUnits::lost_ball
		)
	{
		dynamics.ball->setPosition(
									sf::Vector2f(
													dynamics.ball->getPosition().x,
													dynamics.paddle->getGlobalBounds().top - dynamics.ball->getGlobalBounds().height / 2
												)
		);

		//Y axis acceleration will be inverted
		ball(A_Y) *= -1.f;

		//Bouncing from the PADDLE
		ball(V_X) *= Game::dynamicUnits::bll_bounce;
		ball(V_Y) *= -Game::dynamicUnits::bll_bounce;

		//Now we can accelerate ball with PADDLE IMPULSE
		//ball(V_X) += paddle(V_X);
		//ball(V_Y) += 0.05f * paddle(V_X);  //NOTE: MOVE CONST TO THE CORRECT STORAGE

		//coordinates re-calculation
		ball(DELTA_X) = ball(V_X) * d_time + ball(A_X) * d_time * d_time / 2.f;
		ball(DELTA_Y) = ball(V_Y) * d_time + ball(A_Y) * d_time * d_time / 2.f;

	}

	///!!!
	///BAD SOLUTION
	///!!!
	//FROM THE RIGHT SIDE OF THE PADDLE
	if (
		( (dynamics.ball->getGlobalBounds().top + dynamics.ball->getGlobalBounds().height) > dynamics.paddle->getGlobalBounds().top )
		&&
		( dynamics.ball->getGlobalBounds().left < (dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width) )
		&&
		( dynamics.ball->getPosition().x > dynamics.paddle->getPosition().x )
		&&
		!Game::dynamicUnits::lost_ball
		)
	{
		dynamics.ball->setPosition(
									sf::Vector2f(
													dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width + dynamics.ball->getGlobalBounds().width / 2,
													dynamics.ball->getPosition().y
												)
		);

		////X axis acceleration will be inverted
		//ball(A_X) *= -1.f;

		////Bouncing from the wall
		//ball(V_X) *= -Game::dynamicUnits::bll_bounce;
		//ball(V_Y) *= Game::dynamicUnits::bll_bounce;

		////coordinates re-calculation
		//ball(DELTA_X) = ball(V_X) * d_time + ball(A_X) * d_time * d_time / 2.f;
		//ball(DELTA_Y) = ball(V_Y) * d_time + ball(A_Y) * d_time * d_time / 2.f;

	}

	///!!!
	///BAD SOLUTION
	///!!!
	//FROM THE LEFT SIDE OF THE PADDLE
	if (
		( (dynamics.ball->getGlobalBounds().top + dynamics.ball->getGlobalBounds().height) > dynamics.paddle->getGlobalBounds().top )
		&&
		( (dynamics.ball->getGlobalBounds().left + dynamics.ball->getGlobalBounds().width) > dynamics.paddle->getGlobalBounds().left )
		&&
		( dynamics.ball->getPosition().x < dynamics.paddle->getPosition().x)
		&&
		!Game::dynamicUnits::lost_ball
		)
	{
		dynamics.ball->setPosition(
									sf::Vector2f(
													dynamics.paddle->getGlobalBounds().left - dynamics.ball->getGlobalBounds().width / 2,
													dynamics.ball->getPosition().y
												)
		);

		////X axis acceleration will be inverted
		//ball(A_X) *= -1.f;

		////Bouncing from the wall
		//ball(V_X) *= -Game::dynamicUnits::bll_bounce;
		//ball(V_Y) *= Game::dynamicUnits::bll_bounce;

		////coordinates re-calculation
		//ball(DELTA_X) = ball(V_X) * d_time + ball(A_X) * d_time * d_time / 2.f;
		//ball(DELTA_Y) = ball(V_Y) * d_time + ball(A_Y) * d_time * d_time / 2.f;

	}

}
