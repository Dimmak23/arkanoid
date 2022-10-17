#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> COLLISIONS CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers
#include <cmath>
#include <ranges>
#include <algorithm>

//API


//SFML headers
#include <SFML/Graphics/Rect.hpp>


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
#define BLOCK_TOP			dynamics.conveyor.at(indexer).getGlobalBounds().top
#define BLOCK_BOTTOM		dynamics.conveyor.at(indexer).getGlobalBounds().top + dynamics.conveyor.at(indexer).getGlobalBounds().height
#define BLOCK_LEFT			dynamics.conveyor.at(indexer).getGlobalBounds().left
#define BLOCK_RIGHT			dynamics.conveyor.at(indexer).getGlobalBounds().left + dynamics.conveyor.at(indexer).getGlobalBounds().width

#define ABILITY_CENTER		dynamics.conveyor.at(indexer).getGlobalBounds().left + dynamics.conveyor.at(indexer).getGlobalBounds().width/2 
#define ABILITY_TOP			dynamics.conveyor.at(indexer).getGlobalBounds().top
#define ABILITY_BOTTOM		dynamics.conveyor.at(indexer).getGlobalBounds().top + dynamics.conveyor.at(indexer).getGlobalBounds().height
#define ABILITY_HEIGHT		dynamics.conveyor.at(indexer).getGlobalBounds().height
#define ABILITY_LEFT		dynamics.conveyor.at(indexer).getGlobalBounds().left
#define ABILITY_RIGHT		dynamics.conveyor.at(indexer).getGlobalBounds().left + dynamics.conveyor.at(indexer).getGlobalBounds().width
#define ABILITY_WIDTH		dynamics.conveyor.at(indexer).getGlobalBounds().width

//#define abl(lvalue)			(*res_map_iter).kinematics.at(lvalue)

//#define ITER_TOP			test.getGlobalBounds().top
//#define ITER_BOTTOM			test.getGlobalBounds().top + test.getGlobalBounds().height
//#define ITER_HEIGHT			test.getGlobalBounds().height
//#define ITER_LEFT			test.getGlobalBounds().left
//#define ITER_RIGHT			test.getGlobalBounds().left + test.getGlobalBounds().width
//#define ITER_WIDTH			test.getGlobalBounds().width

#define UNIT_TOP			unit.getGlobalBounds().top
#define UNIT_LEFT			unit.getGlobalBounds().left
#define UNIT_HEIGHT			unit.getGlobalBounds().height
#define UNIT_WIDTH			unit.getGlobalBounds().width
#define UNIT_BOTTOM			UNIT_TOP + UNIT_HEIGHT
#define UNIT_RIGHT			UNIT_LEFT + UNIT_WIDTH
#define U_HOR_TOUCH(coor)	(UNIT_LEFT < coor) && (coor < UNIT_RIGHT)
#define U_VER_TOUCH(coor)	(UNIT_BOTTOM > coor) && (coor > UNIT_TOP)

#define BALL_TOP			dynamics.ball->getGlobalBounds().top
#define BALL_BOTTOM			dynamics.ball->getGlobalBounds().top + dynamics.ball->getGlobalBounds().height
#define BALL_LEFT			dynamics.ball->getGlobalBounds().left
#define BALL_RIGHT			dynamics.ball->getGlobalBounds().left + dynamics.ball->getGlobalBounds().width
#define BALL_HEIGHT			dynamics.ball->getGlobalBounds().height
#define BALL_WIDTH			dynamics.ball->getGlobalBounds().width
#define BALL_RAD			dynamics.ball->getGlobalBounds().width / 2
#define BALL_OX				dynamics.ball->getPosition().x
#define BALL_OY				dynamics.ball->getPosition().y

#define PADDLE_CENTER		dynamics.paddle->getGlobalBounds().top + dynamics.paddle->getGlobalBounds().width/2
#define PADDLE_TOP			dynamics.paddle->getGlobalBounds().top
#define PADDLE_BOTTOM		dynamics.paddle->getGlobalBounds().top + dynamics.paddle->getGlobalBounds().height
#define PADDLE_LEFT			dynamics.paddle->getGlobalBounds().left
#define PADDLE_RIGHT		dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width
#define PADDLE_HEIGHT		dynamics.paddle->getGlobalBounds().height
#define PADDLE_WIDTH		dynamics.paddle->getGlobalBounds().width
#define PADDLE_RAD			to_f(Default::block_height/2)
#define PADDLE_ROX			dynamics.paddle->getGlobalBounds().left + dynamics.paddle->getGlobalBounds().width - to_f(Default::block_height/2)
#define PADDLE_ROY			dynamics.paddle->getGlobalBounds().top - to_f(Default::block_height/2)
#define PADDLE_LOX			dynamics.paddle->getGlobalBounds().left + to_f(Default::block_height/2)
#define PADDLE_LOY			dynamics.paddle->getGlobalBounds().top - to_f(Default::block_height/2)

#define FIRST_BLOCK_BOTTOM	(dynamics.conveyor).at(0).getGlobalBounds().top + (dynamics.conveyor).at(0).getGlobalBounds().height

#define GFIELD_TOP			game_field.origin_y
#define GFIELD_BOTTOM		game_field.origin_y + game_field.overall_height
#define GFIELD_LEFT			game_field.origin_x
#define GFIELD_RIGHT		game_field.origin_x + game_field.overall_width


struct colission_detection
{
	bool diagnose{false};
	sf::Vector2f vector{};

};

inline static void checkLostBall(Game::dynamicUnits& dynamics)
{
	//Let's check are ball lost?
	if ( BALL_TOP >= (GFIELD_BOTTOM + game_field.empty_thk) )
	{
		//Decrement lifes
		if (!Game::dynamicUnits::lost_ball) Game::dynamicUnits::lifes -= 1;

		//Set lost ball status for new ball await
		Game::dynamicUnits::lost_ball = true;

		bll(DELTA_X) = 0;
		bll(DELTA_Y) = 0;
		bll(V_X) = 0;
		bll(V_Y) = 0;
		bll(A_X) = 0;
		bll(A_Y) = 0;
	}
}

inline static colission_detection checkCornerCollision(
	const float& corner_X,
	const float& corner_Y,
	const float& centerX_BLL,
	const float& centerY_BLL,
	const float& rad_BLL
)
{
	colission_detection result;

	float cathetus_sqr_x = to_f(pow((centerX_BLL - corner_X), 2));
	float cathetus_sqr_y = to_f(pow((centerY_BLL - corner_Y), 2));
	float hypotenuse = sqrt(cathetus_sqr_x + cathetus_sqr_y);

	if (hypotenuse < rad_BLL) result.diagnose = true;
	else
	{
		///DON'T GO FURTHER IF THERE IS NO INTERSECTION

		result.diagnose = false;
		result.vector = sf::Vector2f(0, 0);
		return result;
	}

	//Object falling down with angle (in radian units):
	float angle = std::acos((std::abs(centerX_BLL - corner_X)) / hypotenuse);
	float tan_alpha{ std::tan(angle) };

	//Use coupling to avoid division by zero
	//This is possible if ball go thru RIGHT side of the PADDLE,
	//or wise versa,
	//with '0' angle of the SPEED to the ground
	if (std::tan(angle) < 0.01f) tan_alpha = 0.01f;

	//Cathetus by X axis of the intersection:
	//(this is always a positive value)
	float move_x{ (rad_BLL - hypotenuse) / (std::tan(angle)) };

	//If ball go from the LEFT it should be moved to the LEFT
	if (centerX_BLL < corner_X) move_x *= -1.f;
	//positive movement: to the RIGHT

	//USE COUPLING for the X axis, make sure we don't throw ball outside the field

	if ((centerX_BLL + rad_BLL + move_x) > (game_field.origin_x + game_field.overall_width))
	{
		move_x = game_field.origin_x + game_field.overall_width - centerX_BLL - rad_BLL;
	}
	else if ((centerX_BLL - rad_BLL + move_x) < game_field.origin_x)
	{
		move_x = -(centerX_BLL - rad_BLL - game_field.origin_x);
	}

	///GLITCH (BALL GOES TO FAR FROM PADDLE) SOLUTION
	if (move_x > rad_BLL) move_x = rad_BLL;
	else if (move_x < -rad_BLL) move_x = -rad_BLL;

	//We are always go UP from the paddle
	//Cathetus by Y axis of the intersection:
	//always negative, cause will be bounced back - UP
	float move_y = -(rad_BLL - hypotenuse) * (std::tan(angle));

	///GLITCH (BALL GOES TO FAR FROM PADDLE) SOLUTION
	if (move_y > rad_BLL) move_y = rad_BLL;
	else if (move_y < -rad_BLL) move_y = -rad_BLL;

	//So now we can setup a proper vector to the BALL movement
	result.vector = sf::Vector2f(move_x, move_y);

	return result;
}

inline static colission_detection checkCircleCollision(
														const float& centerX_PDL,
														const float& centerY_PDL,
														const float& rad_PDL,
														const float& centerX_BLL,
														const float& centerY_BLL,
														const float& rad_BLL
)
{
	colission_detection result;
	
	float cathetus_sqr_x = to_f(pow((centerX_BLL - centerX_PDL), 2));
	float cathetus_sqr_y = to_f(pow((centerY_BLL - centerY_PDL), 2));
	float hypotenuse = sqrt(cathetus_sqr_x + cathetus_sqr_y);

	if ( hypotenuse < (rad_PDL + rad_BLL) ) result.diagnose = true;
	else
	{
		///DON'T GO FURTHER IF THERE IS NO INTERSECTION

		result.diagnose = false;
		result.vector = sf::Vector2f(0, 0);
		return result;
	}

	//Object falling down with angle (in radian units):
	float angle = std::acos((std::abs(centerX_BLL - centerX_PDL)) / hypotenuse);
	float tan_alpha{ std::tan(angle) };

	//Use coupling to avoid division by zero
	//This is possible if ball go thru RIGHT side of the PADDLE,
	//or wise versa,
	//with '0' angle of the SPEED to the ground
	if ( std::tan(angle) < 0.01f ) tan_alpha = 0.01f;

	//Cathetus by X axis of the intersection:
	//(this is always a positive value)
	float move_x{ (rad_PDL + rad_BLL - hypotenuse) / (std::tan(angle)) };

	//If ball go from the LEFT it should be moved to the LEFT
	if (centerX_BLL < centerX_PDL) move_x *= -1.f;
	//positive movement: to the RIGHT

	//USE COUPLING for the X axis, make sure we don't throw ball outside the field

	if ( (centerX_BLL + rad_BLL + move_x) > (game_field.origin_x + game_field.overall_width) )
	{
		move_x = game_field.origin_x + game_field.overall_width - centerX_BLL - rad_BLL;
	}
	else if ( (centerX_BLL - rad_BLL + move_x) < game_field.origin_x )
	{
		move_x = -(centerX_BLL - rad_BLL - game_field.origin_x);
	}

	///GLITCH (BALL GOES TO FAR FROM PADDLE) SOLUTION
	if (move_x > rad_BLL ) move_x = rad_BLL;
	else if (move_x < -rad_BLL ) move_x = - rad_BLL;
	
	//We are always go UP from the paddle
	//Cathetus by Y axis of the intersection:
	//always negative, cause will be bounced back - UP
	float move_y = - (rad_PDL + rad_BLL - hypotenuse) * (std::tan(angle));

	///GLITCH (BALL GOES TO FAR FROM PADDLE) SOLUTION
	if (move_y > rad_BLL ) move_y = rad_BLL;
	else if (move_y < -rad_BLL ) move_y = - rad_BLL;

	//So now we can setup a proper vector to the BALL movement
	result.vector = sf::Vector2f(move_x, move_y);

	//std::cout << "centerX_BLL - centerX_PDL = " << centerX_BLL - centerX_PDL << '\n';
	//std::cout << "centerY_BLL - centerY_PDL = " << centerY_BLL - centerY_PDL << '\n';
	//std::cout << "hypotenuse = " << hypotenuse << '\n';
	//std::cout << "rad_a + rad_b = " << rad_PDL + rad_BLL << '\n';
	//std::cout << "angle = " << angle << '\n';
	//std::cout << "std::tan(angle) = " << std::tan(angle) << '\n';
	//std::cout << "tan_alpha = " << tan_alpha << '\n';
	//std::cout << "move_x = " << move_x << '\n';
	//std::cout << "move_y = " << move_y << '\n';

	return result;
}

inline static void collideUnits(Game::dynamicUnits& dynamics, const float& d_time)
{

///////////////////////////////////////PADDLE TO WALL////////////////////////////////////////////

	//SLOWDOWN near the LEFT border line
	if (
		(PADDLE_LEFT < GFIELD_LEFT + 20.f)  //15.f pixels near the border is a SLOWDOWN ZONE
		&&
		(dynamics.paddle_kinematics.at(V_X) < 0)  //ONLY IF we going to the border, and NOT out from the border
		)
	{
		pdl(V_X) /= 100;
		pdl(A_X) /= 10000;
	}

	//Let's check are we are hitting the LEFT wall by paddle?
	if (PADDLE_LEFT <= GFIELD_LEFT)
	{
		dynamics.paddle->setPosition(
			sf::Vector2f(
			GFIELD_LEFT + PADDLE_WIDTH / 2,
			to_f(GFIELD_BOTTOM - Default::block_height)
		)
		);

		pdl(A_X) *= -1.f;
		pdl(V_X) *= Game::dynamicUnits::pdl_bounce;
		//dynamics.paddle_kinematics.at(DELTA_X) += 5.f;
		pdl(DELTA_X) = pdl(V_X) * d_time + pdl(A_X) * d_time * d_time / 2.f;

	}

	//SLOWDOWN near the RIGHT border line
	if (
		(PADDLE_RIGHT > (GFIELD_RIGHT - 20.f))
		&&
		(dynamics.paddle_kinematics.at(V_X) > 0.1f)  //ONLY IF we going to the border, and NOT out from the border
		)
	{
		pdl(V_X) /= 100;
		pdl(A_X) /= 10000;
	}

	//Let's check are we are hitting the RIGHT wall by paddle?
	if (PADDLE_RIGHT >= GFIELD_RIGHT)
	{
		dynamics.paddle->setPosition(
			sf::Vector2f(
									GFIELD_RIGHT - PADDLE_WIDTH / 2,
									to_f(GFIELD_BOTTOM - Default::block_height)
								)
		);

		pdl(A_X) *= -1.f;
		pdl(V_X) *= Game::dynamicUnits::pdl_bounce;
		//dynamics.paddle_kinematics.at(DELTA_X) += 5.f;
		pdl(DELTA_X) = pdl(V_X) * d_time + pdl(A_X) * d_time * d_time / 2.f;

	}

///////////////////////////////////////BALL TO WALL////////////////////////////////////////////

	//Let's check are ball hitting the LEFT wall?
	if (BALL_LEFT <= GFIELD_LEFT)
	{
		dynamics.ball->setPosition(
			sf::Vector2f(
			GFIELD_LEFT + BALL_WIDTH / 2,
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
	if (BALL_RIGHT >= GFIELD_RIGHT)
	{
		dynamics.ball->setPosition(
			sf::Vector2f(
			GFIELD_RIGHT - BALL_WIDTH / 2,
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
	if (BALL_TOP <= game_field.origin_y)
	{
		dynamics.ball->setPosition(
			sf::Vector2f(
			dynamics.ball->getPosition().x,
			GFIELD_TOP + BALL_HEIGHT / 2
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

	checkLostBall(dynamics);

/////////////////////////////////////BALL VS PADDLE//////////////////////////////////////////

	//FROM THE TOP OF THE PADDLE
	if (
		//BOTTOM of the BALL go thru paddle top
		(BALL_BOTTOM > PADDLE_TOP)
		//&&
		//(BALL_RIGHT >= PADDLE_LEFT) && (BALL_LEFT <= PADDLE_RIGHT)
		&&
		//AND MOST IMPORTANTLY: it is not a side of the paddle
		(PADDLE_LOX < BALL_OX) && (BALL_OX < PADDLE_ROX)
		&&
		//REMOVING GLITCH
		(!Game::dynamicUnits::lost_ball)
	)
	{
		//std::cout << "TOP side collision...\n";
		
		dynamics.ball->setPosition(
			sf::Vector2f(
			dynamics.ball->getPosition().x,
			PADDLE_TOP - BALL_HEIGHT / 2
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

	//FROM THE LEFT SIDE OF THE PADDLE
	if (
		//BOTTOM of the BALL go thru paddle top
		(BALL_BOTTOM > PADDLE_TOP)
		&&
		//BALL on the LEFT side from the PADDLE, center by X of radius paddle bigger then ball center by X
		(PADDLE_LOX > BALL_OX)
		&&
		//RIGHT side of the BALL got thru LEFT side of the PADDLE
		(BALL_RIGHT > PADDLE_LEFT)
		&&
		//REMOVING GLITCH
		(!Game::dynamicUnits::lost_ball)
	)
	{
		//set up containers to catch result of possible collision
		//And, MOST IMPORTANTLY: Do the circle of the BALL go thru PADDLE circle?
		auto [collision_detection, vector] = checkCircleCollision
		(
		PADDLE_LOX,PADDLE_LOY,PADDLE_RAD,
		BALL_OX,BALL_OY,BALL_RAD
		);

		if(collision_detection)
		{
			//std::cout << "LEFT side collision...\n";
			//std::cout << "PADDLE_LOX = " << PADDLE_LOX << '\n';
			//std::cout << "BALL_OX = " << BALL_OX << '\n';
			
			//Move the ball
			dynamics.ball->move(vector);

			//checkLostBall(dynamics);

			///////////////////RECALCULATE BALL KINEMATICS///////////////////////

			//X axis acceleration will be inverted
			bll(A_X) *= -1.f;
			bll(A_Y) *= -1.f;

			//Bouncing from the wall
			bll(V_X) *= -Game::dynamicUnits::bll_bounce;
			bll(V_Y) *= -Game::dynamicUnits::bll_bounce;

			//Now we can accelerate ball with PADDLE IMPULSE
			bll(V_X) += pdl(V_X);

			//coordinates re-calculation
			bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
			bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;
		}

	}

	//FROM THE RIGHT SIDE OF THE PADDLE
	if (
		//BOTTOM of the BALL go thru paddle top
		(BALL_BOTTOM > PADDLE_TOP)
		&&
		//BALL on the RIGHT side from the PADDLE, center by X of radius paddle less then ball center by X
		(PADDLE_ROX < BALL_OX)
		&&
		//LEFT side of the BALL got thru RIGHT side of the PADDLE
		(BALL_LEFT < PADDLE_RIGHT)
		&&
		//REMOVING GLITCH
		(!Game::dynamicUnits::lost_ball)
	)
	{
		//set up containers to catch result of possible collision
		//And, MOST IMPORTANTLY: Do the circle of the BALL go thru PADDLE circle?
		auto [collision_detection, vector] = checkCircleCollision
		(
			PADDLE_ROX, PADDLE_ROY, PADDLE_RAD,
			BALL_OX, BALL_OY, BALL_RAD
		);

		if (collision_detection)
		{
			//std::cout << "RIGHT side collision...\n";
			//std::cout << "PADDLE_ROX = " << PADDLE_ROX << '\n';
			//std::cout << "BALL_OX = " << BALL_OX << '\n';

			//Move the ball
			dynamics.ball->move(vector);

			//checkLostBall(dynamics);

			///////////////////RECALCULATE BALL KINEMATICS///////////////////////

			//X axis acceleration will be inverted
			bll(A_X) *= -1.f;
			bll(A_Y) *= -1.f;

			//Bouncing from the wall
			bll(V_X) *= -Game::dynamicUnits::bll_bounce;
			bll(V_Y) *= -Game::dynamicUnits::bll_bounce;

			//Now we can accelerate ball with PADDLE IMPULSE
			bll(V_X) += pdl(V_X);

			//coordinates re-calculation
			bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
			bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;
		}

	}

/////////////////////////////////////ABILITIES VS BLOCKS AND ABILITIES//////////////////////////////////////////

	//Go thru all conveyor units

	for (int index{}; index < dynamics.conveyor.size(); )
	{

		for (int inner_index{}; inner_index < index; )
		{
			float top_line = dynamics.conveyor.at(inner_index).getGlobalBounds().top;
			float bottom_line = dynamics.conveyor.at(index).getGlobalBounds().top + dynamics.conveyor.at(index).getGlobalBounds().height;

			float above_left = dynamics.conveyor.at(index).getGlobalBounds().left;
			float under_left = dynamics.conveyor.at(inner_index).getGlobalBounds().left;

			sf::FloatRect abil;
			abil.left = above_left;
			abil.top = dynamics.conveyor.at(index).getGlobalBounds().top;
			abil.width = dynamics.conveyor.at(index).getGlobalBounds().width;
			abil.height = dynamics.conveyor.at(index).getGlobalBounds().height;

			sf::FloatRect iterated;
			iterated.left = under_left;
			iterated.top = dynamics.conveyor.at(inner_index).getGlobalBounds().top;
			iterated.width = dynamics.conveyor.at(inner_index).getGlobalBounds().width;
			iterated.height = dynamics.conveyor.at(inner_index).getGlobalBounds().height;

			if (abil.findIntersection(iterated).has_value() == true )
			{
				dynamics.conveyor_map.at(index).kinematics.at(V_Y) = 0;

				dynamics.conveyor.at(index).setPosition(sf::Vector2f(
					dynamics.conveyor.at(inner_index).getGlobalBounds().left,
					dynamics.conveyor.at(inner_index).getGlobalBounds().top - dynamics.conveyor.at(index).getGlobalBounds().height)
				);
				//std::cout << "Hold this" << index << '\n';
			}
			else
			{
				dynamics.conveyor_map.at(index).kinematics.at(V_Y) = Game::dynamicUnits::abl_V_step;

			}
			inner_index++;
		}
		index++;
	}

/////////////////////////////////////LOST ABILITIES//////////////////////////////////////////

	//Let's check are the ability lost?

	//Go thru all conveyor units

	///std::ranges COULD be used here

	auto out_of_field = [&](const sf::Sprite& test)
	{
		return ( test.getGlobalBounds().top >= (GFIELD_BOTTOM + game_field.empty_thk) );
	};

	auto erase_this_abl = std::ranges::find_if(dynamics.conveyor, out_of_field);

	if (erase_this_abl != dynamics.conveyor.end())
	{
		int this_index{ to_i(erase_this_abl - dynamics.conveyor.begin()) };
		auto erase_this_map = dynamics.conveyor_map.begin() + this_index;

		dynamics.conveyor.erase(erase_this_abl);
		dynamics.conveyor_map.erase(erase_this_map);
	}

////////////////////////////////////PADDLE VS ABILITIES///////////////////////////////////////////

	for (int indexer{}; indexer < dynamics.conveyor.size(); )
	{
		if (dynamics.conveyor_map.at(indexer).block)
		{
			//move along
			indexer++;
			continue;
		}
		
		//FROM THE TOP OF THE PADDLE
		if (
			//BOTTOM of the ABILITY go thru paddle top
			(ABILITY_BOTTOM > PADDLE_TOP)
			&&
			( 
				(ABILITY_LEFT >= PADDLE_LEFT) && (ABILITY_LEFT <= PADDLE_RIGHT)
				||
				(ABILITY_RIGHT >= PADDLE_LEFT) && (ABILITY_RIGHT <= PADDLE_RIGHT)
				||
				//For small PADDLE
				(PADDLE_CENTER >= ABILITY_LEFT) && (PADDLE_CENTER <= ABILITY_LEFT)
			)
			//&&
			//REMOVING GLITCH
			//(!Game::dynamicUnits::lost_ball)
			)
		{
			//std::cout << "TOP side ability collision...\n";

			//Choose function to execute
			executor do_this{ dynamics.conveyor_map.at(indexer).function };

			//Pass variable to that function
			do_this(dynamics.conveyor_map.at(indexer).operand);

			//AND of course destroy such block
			auto eraser_unit = dynamics.conveyor.begin() + indexer;

			//Also destory a mapper for such block
			auto eraser_mapper = dynamics.conveyor_map.begin() + indexer;

			dynamics.conveyor_map.erase(eraser_mapper);
			dynamics.conveyor.erase(eraser_unit);

		}
		else indexer++;

		////FROM THE LEFT SIDE OF THE PADDLE
		//if (
		//	//BOTTOM of the ABILITY go thru paddle top
		//	(ABILITY_BOTTOM > PADDLE_TOP)
		//	&&
		//	//ABILITY on the LEFT side from the PADDLE, center by X of radius paddle bigger then ball center by X
		//	(PADDLE_LOX > ABILITY_OX)
		//	&&
		//	//RIGHT side of the ABILITY got thru LEFT side of the PADDLE
		//	(ABILITY_RIGHT > PADDLE_LEFT)
		//	//&&
		//	//REMOVING GLITCH
		//	//(!Game::dynamicUnits::lost_ball)
		//	)
		//{
		//	//set up containers to catch result of possible collision
		//	//And, MOST IMPORTANTLY: Do the circle of the ABILITY go thru PADDLE circle?
		//	//auto [collision_detection, vector] = checkCircleCollision
		//	//(
		//	//	PADDLE_LOX, PADDLE_LOY, PADDLE_RAD,
		//	//	ABILITY_OX, ABILITY_OY, ABILITY_RAD
		//	//);

		//	//if (collision_detection)
		//	//{
		//	std::cout << "LEFT side ability collision...\n";

		////}

		//}

		////FROM THE RIGHT SIDE OF THE PADDLE
		//if (
		//	//BOTTOM of the ABILITY go thru paddle top
		//	(ABILITY_BOTTOM > PADDLE_TOP)
		//	&&
		//	//ABILITY on the RIGHT side from the PADDLE, center by X of radius paddle less then ball center by X
		//	(PADDLE_ROX < ABILITY_OX)
		//	&&
		//	//LEFT side of the ABILITY got thru RIGHT side of the PADDLE
		//	(ABILITY_LEFT < PADDLE_RIGHT)
		//	//&&
		//	//REMOVING GLITCH
		//	//(!Game::dynamicUnits::lost_ball)
		//	)
		//{
		//	//set up containers to catch result of possible collision
		//	//And, MOST IMPORTANTLY: Do the circle of the ABILITY go thru PADDLE circle?
		//	//auto [collision_detection, vector] = checkCircleCollision
		//	//(
		//	//	PADDLE_ROX, PADDLE_ROY, PADDLE_RAD,
		//	//	ABILITY_OX, ABILITY_OY, ABILITY_RAD
		//	//);

		//	//if (collision_detection)
		//	//{
		//	std::cout << "RIGHT side collision...\n";

		////}

		//}
	}

}

//static inline bool one_timer_b{ true };
//static inline bool one_timer_a{ true };

inline static void hitUnits(Game::dynamicUnits& dynamics, const float& d_time)
{
	//if(one_timer_b)
	//{
	//	for (int index{}; index < dynamics.conveyor_map.size(); index++)
	//	{
	//		if (dynamics.conveyor_map.at(index).block)
	//		{
	//			if (one_timer_b)
	//			{
	//				std::cout << "Block width = " << dynamics.conveyor.at(index).getGlobalBounds().width << '\n';
	//				std::cout << "Block height = " << dynamics.conveyor.at(index).getGlobalBounds().height << '\n';
	//			}
	//			one_timer_b = false;
	//			continue;
	//		}

	//		if(one_timer_a)
	//		{
	//			std::cout << "Ability width = " << dynamics.conveyor.at(index).getGlobalBounds().width << '\n';
	//			std::cout << "Ability height = " << dynamics.conveyor.at(index).getGlobalBounds().height << '\n';
	//			one_timer_a = false;
	//		}
	//	}
	//}
	

/////////////////////////////////////BALL VS CONVEYOR BELT//////////////////////////////////////////

	//First of all, let's go out from this function if ball are bellow the BELT
	if (BALL_TOP > FIRST_BLOCK_BOTTOM)
		return;

	//If not, then we can talk
	//int indexer{};
	std::vector<sf::Sprite>::iterator eraser_unit;
	std::vector<Game::block_map_variables>::iterator eraser_mapper;

	//for (int indexer{}; indexer < dynamics.conveyor.size(); )
	//{
	//	if (
	//			(
	//				//LEFT side of the BALL between BLOCK bounds
	//				(BLOCK_LEFT < BALL_LEFT) && (BALL_LEFT < BLOCK_RIGHT)
	//				||
	//				//OR
	//				//RIGHT side of the BALL between BLOCK bounds
	//				(BLOCK_LEFT < BALL_RIGHT) && (BALL_RIGHT < BLOCK_RIGHT)
	//			)
	//		&&
	//			(
	//				//TOP of the BALL between BLOCK bounds
	//				(BLOCK_TOP < BALL_TOP) && (BALL_TOP < BLOCK_BOTTOM)
	//				||
	//				//OR
	//				//BOTTOM of the BALL between BLOCK bounds
	//				(BLOCK_TOP < BALL_BOTTOM) && (BALL_BOTTOM < BLOCK_BOTTOM)
	//			)
	//		)
	//	{

	//		if ( std::abs(bll(V_X)) > std::abs(bll(V_Y)) )
	//		{
	//			//Y axis acceleration speed will be inverted
	//			bll(A_Y) *= -1.f;

	//			//Bouncing from the block
	//			bll(V_X) *= Game::dynamicUnits::bll_bounce;
	//			bll(V_Y) *= -Game::dynamicUnits::bll_bounce;
	//		}
	//		else if ( std::abs(bll(V_X)) < std::abs(bll(V_Y)) )
	//		{
	//			//X axis acceleration and speed will be inverted
	//			bll(A_X) *= -1.f;

	//			//Bouncing from the block
	//			bll(V_X) *= -Game::dynamicUnits::bll_bounce;
	//			bll(V_Y) *= Game::dynamicUnits::bll_bounce;
	//		}
	//		else
	//		{
	//			//BOTH axis accelerations and speeds will be inverted
	//			bll(A_X) *= -1.f;
	//			bll(A_Y) *= -1.f;

	//			//Bouncing from the block
	//			bll(V_Y) *= -Game::dynamicUnits::bll_bounce;
	//			bll(V_Y) *= Game::dynamicUnits::bll_bounce;
	//		}

	//		//coordinates re-calculation
	//		bll(DELTA_X) = bll(V_X) * d_time + bll(A_X) * d_time * d_time / 2.f;
	//		bll(DELTA_Y) = bll(V_Y) * d_time + bll(A_Y) * d_time * d_time / 2.f;

	//		//Take deltas from kinematic container and move the ball
	//		dynamics.ball->move(sf::Vector2f(bll(DELTA_X), bll(DELTA_Y)));

	//		//If it's a block, we increase score and erase it then
	//		if (dynamics.conveyor_map.at(indexer).block)
	//		{
	//			//Choose function to execute
	//			executor do_this{ dynamics.conveyor_map.at(indexer).function};

	//			//Pass variable to that function
	//			do_this(dynamics.conveyor_map.at(indexer).operand);

	//			//AND of course destroy such block
	//			eraser_unit = dynamics.conveyor.begin() + indexer;

	//			//Also destory a mapper for such block
	//			eraser_mapper = dynamics.conveyor_map.begin() + indexer;
	//			
	//			dynamics.conveyor_map.erase(eraser_mapper);
	//			dynamics.conveyor.erase(eraser_unit);

	//		}
	//		//If it's an ability: bounce from it
	//		else
	//		{
	//		
	//		}

	//		//NOT necassary to traverse the hall container
	//		//if one hitted already we need to find another one in the next frame
	//		//return;
	//	}
	//	///NOT SURE ABOUT THIS
	//	//IF we erase some block: indexer will be lead to the next one already
	//	//BUT! if we didn't delete anything: we will increment position in the container
	//	else indexer++;
	//}

	//Seed for only blocks
	auto only_blocks = [](const Game::block_map_variables& struc)
	{
		return struc.block;
	};


	//If there is gonna be a collision?
	auto bounds_collision = [&](const sf::Sprite& unit)
	{
		return
			(
			(U_HOR_TOUCH(BALL_LEFT) && (U_VER_TOUCH(BALL_TOP) || U_VER_TOUCH(BALL_BOTTOM)))
			||
			(U_HOR_TOUCH(BALL_RIGHT) && (U_VER_TOUCH(BALL_TOP) || U_VER_TOUCH(BALL_BOTTOM)))
			);
	};
	
	int map_adder{};

	auto attacked_unit = dynamics.conveyor.begin();
	
	while(attacked_unit != dynamics.conveyor.end())
	{
		auto give_block = std::ranges::find_if(dynamics.conveyor_map.begin() + map_adder, dynamics.conveyor_map.end(), only_blocks);
	
		if (give_block != dynamics.conveyor_map.end())
		{
			attacked_unit = dynamics.conveyor.begin() + (give_block - dynamics.conveyor_map.begin());
			map_adder = give_block - dynamics.conveyor_map.begin() + 1;
		}
		else attacked_unit = dynamics.conveyor.end();

		auto attacked_block = std::ranges::find_if(attacked_unit, dynamics.conveyor.end(), bounds_collision);

#define BALL_UL_CORNER ()&&()

		//If corner
		if(
			()
		)
		{
		
		}


		//If flat surface

	}



}
