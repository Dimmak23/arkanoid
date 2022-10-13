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



//Forward declaration
//struct Game::block_map_variables
//{
//	bool block;				//Here would be: true, if it is a block; and: false, if it is an ability
//	float operand;			//Here we are passing operand for executor function: points to add, multiplier for speed,...
//	executor function;		//pointer to function that have to be executed
//};



//DEFINES
#define BLOCK_TOP			(*unit).getGlobalBounds().top
#define BLOCK_BOTTOM		(*unit).getGlobalBounds().top + (*unit).getGlobalBounds().height
#define BLOCK_LEFT			(*unit).getGlobalBounds().left
#define BLOCK_RIGHT			(*unit).getGlobalBounds().left + (*unit).getGlobalBounds().width

#define BALL_TOP			dynamics.ball->getGlobalBounds().top
#define BALL_BOTTOM			dynamics.ball->getGlobalBounds().top + dynamics.ball->getGlobalBounds().height
#define BALL_LEFT			dynamics.ball->getGlobalBounds().left
#define BALL_RIGHT			dynamics.ball->getGlobalBounds().left + dynamics.ball->getGlobalBounds().width

#define FIRST_BLOCK_BOTTOM	(dynamics.conveyor).at(0)->getGlobalBounds().top + (dynamics.conveyor).at(0)->getGlobalBounds().height



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
		pdl(V_X) /= 100;
		pdl(A_X) /= 10000;
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

		pdl(A_X) *= -1.f;
		pdl(V_X) *= Game::dynamicUnits::pdl_bounce;
		//dynamics.paddle_kinematics.at(DELTA_X) += 5.f;
		pdl(DELTA_X) = pdl(V_X) * d_time + pdl(A_X) * d_time * d_time / 2.f;

	}

	//SLOWDOWN near the RIGHT border line
	if (
		( (dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width) > (game_field.origin_x + game_field.overall_width - 20.f) )
		&&
		(dynamics.paddle_kinematics.at(V_X) > 0.1f)  //ONLY IF we going to the border, and NOT out from the border
		)
	{
		pdl(V_X) /= 100;
		pdl(A_X) /= 10000;
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

		pdl(A_X) *= -1.f;
		pdl(V_X) *= Game::dynamicUnits::pdl_bounce;
		//dynamics.paddle_kinematics.at(DELTA_X) += 5.f;
		pdl(DELTA_X) = pdl(V_X) * d_time + pdl(A_X) * d_time * d_time / 2.f;

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
		bll(A_X) *= -1.f;

		//Bouncing from the wall
		bll(V_X) *= -Game::dynamicUnits::bll_bounce;
		bll(V_Y) *= Game::dynamicUnits::bll_bounce;

		//coordinates re-calculation
		bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
		bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;

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
		bll(A_X) *= -1.f;

		//Bouncing from the wall
		bll(V_X) *= -Game::dynamicUnits::bll_bounce;
		bll(V_Y) *= Game::dynamicUnits::bll_bounce;

		//coordinates re-calculation
		bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
		bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;

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
		bll(A_Y) *= -1.f;

		//Bouncing from the wall
		bll(V_X) *= Game::dynamicUnits::bll_bounce;
		bll(V_Y) *= -Game::dynamicUnits::bll_bounce;

		//coordinates re-calculation
		bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
		bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;

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
		bll(A_Y) *= -1.f;

		//Bouncing from the PADDLE
		bll(V_X) *= Game::dynamicUnits::bll_bounce;
		bll(V_Y) *= -Game::dynamicUnits::bll_bounce;

		//Now we can accelerate ball with PADDLE IMPULSE
		//bll(V_X) += pdl(V_X);
		bll(V_X) += Game::dynamicUnits::bll_mult * pdl(V_X);

		//coordinates re-calculation
		bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
		bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;

	}

	///!!!
	///BAD SOLUTION
	///!!!
	//FROM THE RIGHT SIDE OF THE PADDLE
	if (
		//BOTTOM of the BALL go thru paddle top
		( (dynamics.ball->getGlobalBounds().top + dynamics.ball->getGlobalBounds().height) > dynamics.paddle->getGlobalBounds().top )
		&&
		//LEFT side of the BALL got thru RIGHT side of the PADDLE
		( dynamics.ball->getGlobalBounds().left < (dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width) )
		&&
		//BALL on the RIGHT side from the PADDLE
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

		//X axis acceleration will be inverted
		bll(A_X) *= -1.f;

		//Bouncing from the wall
		bll(V_X) *= -Game::dynamicUnits::bll_bounce;
		bll(V_Y) *= Game::dynamicUnits::bll_bounce;

		//coordinates re-calculation
		bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
		bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;

	}

	///!!!
	///BAD SOLUTION
	///!!!
	//FROM THE LEFT SIDE OF THE PADDLE
	if (
		//BOTTOM of the BALL go thru paddle top
		( (dynamics.ball->getGlobalBounds().top + dynamics.ball->getGlobalBounds().height) > dynamics.paddle->getGlobalBounds().top )
		&&
		//RIGHT side of the BALL got thru LEFT side of the PADDLE
		( (dynamics.ball->getGlobalBounds().left + dynamics.ball->getGlobalBounds().width) > dynamics.paddle->getGlobalBounds().left )
		&&
		//BALL on the LEFT side from the PADDLE
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

		//X axis acceleration will be inverted
		bll(A_X) *= -1.f;

		//Bouncing from the wall
		bll(V_X) *= -Game::dynamicUnits::bll_bounce;
		bll(V_Y) *= Game::dynamicUnits::bll_bounce;

		//coordinates re-calculation
		bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
		bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;

	}

}

inline static void hitUnits(Game::dynamicUnits& dynamics, const float& d_time)
{

/////////////////////////////////////BALL VS CONVEYOR BELT//////////////////////////////////////////

	//First of all, let's go out from this function if ball are bellow the BELT
	if (BALL_TOP > FIRST_BLOCK_BOTTOM)
		return;

	//If not, then we can talk
	int indexer{};
	std::vector<std::unique_ptr<sf::Sprite>>::iterator eraser_unit;
	std::vector<Game::block_map_variables>::iterator eraser_mapper;

	for (auto& unit : dynamics.conveyor)
	{
		if (
				(
					//LEFT side of the BALL between BLOCK bounds
					(BLOCK_LEFT < BALL_LEFT) && (BALL_LEFT < BLOCK_RIGHT)
					||
					//OR
					//RIGHT side of the BALL between BLOCK bounds
					(BLOCK_LEFT < BALL_RIGHT) && (BALL_RIGHT < BLOCK_RIGHT)
				)
			&&
				(
					//TOP of the BALL between BLOCK bounds
					(BLOCK_TOP < BALL_TOP) && (BALL_TOP < BLOCK_BOTTOM)
					||
					//OR
					//BOTTOM of the BALL between BLOCK bounds
					(BLOCK_TOP < BALL_BOTTOM) && (BALL_BOTTOM < BLOCK_BOTTOM)
				)
			)
		{

			if ( std::abs(bll(V_X)) > std::abs(bll(V_Y)) )
			{
				//Y axis acceleration speed will be inverted
				bll(A_Y) *= -1.f;

				//Bouncing from the block
				bll(V_X) *= Game::dynamicUnits::bll_bounce;
				bll(V_Y) *= -Game::dynamicUnits::bll_bounce;
			}
			else if ( std::abs(bll(V_X)) < std::abs(bll(V_Y)) )
			{
				//X axis acceleration and speed will be inverted
				bll(A_X) *= -1.f;

				//Bouncing from the block
				bll(V_X) *= -Game::dynamicUnits::bll_bounce;
				bll(V_Y) *= Game::dynamicUnits::bll_bounce;
			}
			else
			{
				//BOTH axis accelerations and speeds will be inverted
				bll(A_X) *= -1.f;
				bll(A_Y) *= -1.f;

				//Bouncing from the block
				bll(V_Y) *= -Game::dynamicUnits::bll_bounce;
				bll(V_Y) *= Game::dynamicUnits::bll_bounce;
			}

			//coordinates re-calculation
			bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
			bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;

			//Take deltas from kinematic container and move the ball
			dynamics.ball->move(sf::Vector2f(bll(DELTA_X), bll(DELTA_Y)));

			//If it's a block, we increase score and erase it then
			if (dynamics.conveyor_map.at(indexer).block)
			{
				//Choose function to execute
				executor do_this{ dynamics.conveyor_map.at(indexer).function};

				//Pass variable to that function
				do_this(dynamics.conveyor_map.at(indexer).operand);

				//AND of course destroy such block
				eraser_unit = dynamics.conveyor.begin() + indexer;

				//Also destory a mapper for such block
				eraser_mapper = dynamics.conveyor_map.begin() + indexer;
				
				dynamics.conveyor_map.erase(eraser_mapper);
				dynamics.conveyor.erase(eraser_unit);

			}

			//NOT necassary to traverse the hall container
			//if one hitted already we will find another one in the next frame
			return;
		}
		indexer++;
	}

}
