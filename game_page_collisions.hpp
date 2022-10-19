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
#include <exception>
#include <cassert>


//API


//SFML headers
#include <SFML/Graphics/Rect.hpp>


//Custom headers
//#include "util.hpp"
#include "game_page.hpp"
//#include "game_page_statics.hpp"
#include "game_page_dynamics.hpp"
//#include "game_page_process.hpp"


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

#define INDEXER_LEFT		dynamics.conveyor.at(index).getGlobalBounds().left
#define INDEXER_WIDTH		dynamics.conveyor.at(index).getGlobalBounds().width
#define INDEXER_RIGHT		INDEXER_LEFT + INDEXER_WIDTH
#define INDEXER_TOP			dynamics.conveyor.at(index).getGlobalBounds().top
#define INDEXER_HEIGHT		dynamics.conveyor.at(index).getGlobalBounds().height
#define INDEXER_BOTTOM		INDEXER_TOP + INDEXER_HEIGHT

#define HOLDER_LEFT			dynamics.conveyor.at(holder_index).getGlobalBounds().left
#define HOLDER_WIDTH		dynamics.conveyor.at(holder_index).getGlobalBounds().width
#define HOLDER_RIGHT		HOLDER_LEFT + HOLDER_WIDTH
#define HOLDER_TOP			dynamics.conveyor.at(holder_index).getGlobalBounds().top
#define HOLDER_HEIGHT		dynamics.conveyor.at(holder_index).getGlobalBounds().height
#define HOLDER_BOTTOM		HOLDER_TOP + HOLDER_HEIGHT

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

#define BALL_DX				dynamics.ball_kinematics.at(DELTA_X)
#define BALL_DY				dynamics.ball_kinematics.at(DELTA_Y)
#define BALL_VX				dynamics.ball_kinematics.at(V_X)
#define BALL_VY				dynamics.ball_kinematics.at(V_Y)
#define BALL_AX				dynamics.ball_kinematics.at(A_X)
#define BALL_AY				dynamics.ball_kinematics.at(A_Y)

#define ABLOCK_TOP			(*attacked_unit).getGlobalBounds().top
#define ABLOCK_LEFT			(*attacked_unit).getGlobalBounds().left
#define ABLOCK_HEIGHT		(*attacked_unit).getGlobalBounds().height
#define ABLOCK_WIDTH		(*attacked_unit).getGlobalBounds().width
#define ABLOCK_BOTTOM		ABLOCK_TOP + ABLOCK_HEIGHT
#define ABLOCK_RIGHT		ABLOCK_LEFT + ABLOCK_WIDTH

#define THIS_ABL_TOP		(*this_unit).getGlobalBounds().top
#define THIS_ABL_LEFT		(*this_unit).getGlobalBounds().left
#define THIS_ABL_HEIGHT		(*this_unit).getGlobalBounds().height
#define THIS_ABL_WIDTH		(*this_unit).getGlobalBounds().width
#define THIS_ABL_BOTTOM		THIS_ABL_TOP + THIS_ABL_HEIGHT
#define THIS_ABL_RIGHT		THIS_ABL_LEFT + THIS_ABL_WIDTH
#define THIS_ABL_RAD		THIS_ABL_HEIGHT / 2
#define THIS_ABL_X_CENTER	(*this_unit).getGlobalBounds().left + THIS_ABL_WIDTH/2
#define THIS_ABL_Y_CENTER	THIS_ABL_TOP + THIS_ABL_RAD
#define THIS_ABL_RX_LEFT	THIS_ABL_LEFT + THIS_ABL_RAD
#define THIS_ABL_RX_RIGHT	THIS_ABL_RIGHT - THIS_ABL_RAD
#define THIS_ABL_L_SIDE		(THIS_ABL_Y_CENTER < ABLOCK_BOTTOM) && (THIS_ABL_Y_CENTER > ABLOCK_TOP) && (THIS_ABL_RIGHT < ABLOCK_RIGHT)
#define THIS_ABL_R_SIDE		(THIS_ABL_Y_CENTER < ABLOCK_BOTTOM) && (THIS_ABL_Y_CENTER > ABLOCK_TOP) && (THIS_ABL_LEFT > ABLOCK_LEFT)
#define THIS_ABL_T_SIDE		(THIS_ABL_X_CENTER < ABLOCK_RIGHT) && (THIS_ABL_X_CENTER > ABLOCK_LEFT) && (THIS_ABL_BOTTOM > ABLOCK_TOP)
#define THIS_ABL_B_SIDE		(THIS_ABL_X_CENTER < ABLOCK_RIGHT) && (THIS_ABL_X_CENTER > ABLOCK_LEFT) && (THIS_ABL_TOP < ABLOCK_BOTTOM)
#define THIS_ABL_UL_CORNER	(THIS_ABL_RX_RIGHT < ABLOCK_LEFT) && (THIS_ABL_Y_CENTER < ABLOCK_TOP)
#define THIS_ABL_BL_CORNER	(THIS_ABL_RX_RIGHT < ABLOCK_LEFT) && (THIS_ABL_Y_CENTER > ABLOCK_BOTTOM)
#define THIS_ABL_UR_CORNER	(THIS_ABL_RX_LEFT > ABLOCK_RIGHT) && (THIS_ABL_Y_CENTER < ABLOCK_TOP)
#define THIS_ABL_BR_CORNER	(THIS_ABL_RX_LEFT > ABLOCK_RIGHT) && (THIS_ABL_Y_CENTER > ABLOCK_BOTTOM)

#define T_HOR_TOUCH(coor)	(ABLOCK_LEFT < coor) && (coor < ABLOCK_RIGHT)
#define T_VER_TOUCH(coor)	(ABLOCK_BOTTOM > coor) && (coor > ABLOCK_TOP)

#define THIS_MAP_DX			(*this_map).kinematics.at(DELTA_X)
#define THIS_MAP_DY			(*this_map).kinematics.at(DELTA_Y)
#define THIS_MAP_VX			(*this_map).kinematics.at(V_X)
#define THIS_MAP_VY			(*this_map).kinematics.at(V_Y)
#define THIS_MAP_AX			(*this_map).kinematics.at(A_X)
#define THIS_MAP_AY			(*this_map).kinematics.at(A_Y)

#define AABL_TOP			(*attacked_unit).getGlobalBounds().top
#define AABL_LEFT			(*attacked_unit).getGlobalBounds().left
#define AABL_HEIGHT			(*attacked_unit).getGlobalBounds().height
#define AABL_RAD			(*attacked_unit).getGlobalBounds().height / 2
#define AABL_WIDTH			(*attacked_unit).getGlobalBounds().width
#define AABL_BOTTOM			AABL_TOP + AABL_HEIGHT
#define AABL_RIGHT			AABL_LEFT + AABL_WIDTH
#define AABL_Y_CENTER		AABL_TOP + AABL_RAD
#define AABL_RX_LEFT		AABL_LEFT + AABL_RAD
#define AABL_RX_RIGHT		AABL_RIGHT - AABL_RAD

#define BALL_UL_CORNER		(BALL_OX < ABLOCK_LEFT) && (BALL_OY < ABLOCK_TOP)
#define BALL_BL_CORNER		(BALL_OX < ABLOCK_LEFT) && (BALL_OY > ABLOCK_BOTTOM)
#define BALL_UR_CORNER		(BALL_OX > ABLOCK_RIGHT) && (BALL_OY < ABLOCK_TOP)
#define BALL_BR_CORNER		(BALL_OX > ABLOCK_RIGHT) && (BALL_OY > ABLOCK_BOTTOM)
#define BALL_L_SIDE			(BALL_OY < ABLOCK_BOTTOM) && (BALL_OY > ABLOCK_TOP) && (BALL_RIGHT < ABLOCK_RIGHT)
#define BALL_R_SIDE			(BALL_OY < ABLOCK_BOTTOM) && (BALL_OY > ABLOCK_TOP) && (BALL_LEFT > ABLOCK_LEFT)
#define BALL_T_SIDE			(BALL_OX < ABLOCK_RIGHT) && (BALL_OX > ABLOCK_LEFT) && (BALL_TOP < ABLOCK_TOP)
#define BALL_B_SIDE			(BALL_OX < ABLOCK_RIGHT) && (BALL_OX > ABLOCK_LEFT) && (BALL_BOTTOM > ABLOCK_BOTTOM)

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
														const float& rad_BLL,
														const float& dy_BLL
)
{
	colission_detection result;

	float cathetus_sqr_x = to_f(pow((centerX_BLL - corner_X), 2));
	float cathetus_sqr_y = to_f(pow((centerY_BLL - corner_Y), 2));
	float hypotenuse = sqrt(cathetus_sqr_x + cathetus_sqr_y);

	//if (hypotenuse < rad_BLL) result.diagnose = true;
	//else
	//{
	//	///DON'T GO FURTHER IF THERE IS NO INTERSECTION
	//	result.diagnose = false;
	//	result.vector = sf::Vector2f(0, 0);
	//	return result;
	//}

	///It's seems that we already check that collision exist
	result.diagnose = true;

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
	//NOTE: we move ball by setPosition() and ball could be inside block before it
	//So we are setting cathetus of ball radius to axis X
	float move_x{ (rad_BLL) / (std::tan(angle)) };

	//If ball go from the LEFT it should be moved to the LEFT
	if (centerX_BLL < corner_X) move_x *= -1.f;
	//positive movement: to the RIGHT

	//USE COUPLING for the X axis, make sure we don't throw ball outside the field
	if ((centerX_BLL + 2*rad_BLL + move_x) > (game_field.origin_x + game_field.overall_width))
	{
		move_x = game_field.origin_x + game_field.overall_width - centerX_BLL - 2*rad_BLL;
	}
	else if ((centerX_BLL - 2*rad_BLL + move_x) < game_field.origin_x)
	{
		move_x = -(centerX_BLL - 2*rad_BLL - game_field.origin_x);
	}

	///GLITCH (BALL GOES TO FAR FROM PADDLE) SOLUTION
	if (move_x > rad_BLL) move_x = rad_BLL;
	else if (move_x < -rad_BLL) move_x = -rad_BLL;

	//If BALL go from UP it should come UP,
	//If BALL go from DOWN it should come down.
	//NOTE: we move ball by setPosition() and ball could be inside block before it
	//So we are setting cathetus of ball radius to axis X
	float move_y{};
	//If coming from DOWN (dy_BLL<0)
	if(dy_BLL != std::abs(dy_BLL)) move_y = (rad_BLL) * (std::tan(angle));
	//If coming from UP (dy_BLL>0)
	else move_y = -(rad_BLL) * (std::tan(angle));

	///GLITCH (BALL GOES TO FAR FROM PADDLE) SOLUTION
	if (move_y > rad_BLL) move_y = rad_BLL;
	else if (move_y < -rad_BLL) move_y = -rad_BLL;

	//And FINALLY go to the absolute values:
	move_x += corner_X;
	move_y += corner_Y;

	//So now we can setup a proper vector to the BALL positioning
	result.vector = sf::Vector2f(move_x, move_y);

	return result;
}

inline static colission_detection checkCircleCollision(
														const float& centerX_PDL,
														const float& centerY_PDL,
														const float& rad_PDL,
														const float& centerX_BLL,
														const float& centerY_BLL,
														const float& rad_BLL,
														const float& dy_BLL = 0.f
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
	//BUT! We are not always go to the TOP of ABILITY
	float move_y{};
	//If coming from DOWN (dy_BLL<0)
	if (dy_BLL != std::abs(dy_BLL)) move_y = (rad_PDL + rad_BLL - hypotenuse) * (std::tan(angle));
	//If coming from UP (dy_BLL>0)
	else move_y = -(rad_PDL + rad_BLL - hypotenuse) * (std::tan(angle));

	///GLITCH (BALL GOES TO FAR FROM PADDLE) SOLUTION
	if (move_y > rad_BLL ) move_y = rad_BLL;
	else if (move_y < -rad_BLL ) move_y = - rad_BLL;

	//So now we can setup a proper vector to the BALL movement
	result.vector = sf::Vector2f(move_x, move_y);

	return result;
}

inline static void collideUnits(Game::dynamicUnits& dynamics, const float& d_time)
{

///////////////////////////////////////PADDLE TO WALL////////////////////////////////////////////

	//SLOWDOWN near the LEFT border line
	if (
		(PADDLE_LEFT < GFIELD_LEFT + 10.f)  //10.f pixels near the border is a SLOWDOWN ZONE
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
		(PADDLE_RIGHT > (GFIELD_RIGHT - 10.f))
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

////////////////////////////////////////////PADDLE VS ABILITIES///////////////////////////////////////////

	for (int indexer{}; indexer < dynamics.conveyor.size(); )
	{
		if (dynamics.conveyor_map.at(indexer).block)
		{
			//move along
			indexer++;
			continue;
		}
		
		sf::Rect ABL_BODY(sf::Vector2f(ABILITY_LEFT, ABILITY_TOP), sf::Vector2f(ABILITY_WIDTH, ABILITY_HEIGHT));
		sf::Rect PADDLE_BODY(sf::Vector2f(PADDLE_LEFT, PADDLE_TOP), sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));

		//FROM THE TOP OF THE PADDLE
		//if (
		//	//BOTTOM of the ABILITY go thru paddle top
		//	(ABILITY_BOTTOM >= PADDLE_TOP)
		//	&&
		//	( 
		//		(ABILITY_LEFT >= PADDLE_LEFT) && (ABILITY_LEFT <= PADDLE_RIGHT)
		//		||
		//		(ABILITY_RIGHT >= PADDLE_LEFT) && (ABILITY_RIGHT <= PADDLE_RIGHT)
		//		||
		//		//For small PADDLE
		//		(PADDLE_CENTER >= ABILITY_LEFT) && (PADDLE_CENTER <= ABILITY_RIGHT)
		//	)
		//	//REMOVING GLITCH
		//	//&&
		//	//(!Game::dynamicUnits::lost_ball)
		//)

		auto diagnose = ABL_BODY.findIntersection(PADDLE_BODY);

		if(diagnose.has_value())
		{
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
	}
}

static inline void ablHitPlayGround(Game::dynamicUnits& dynamics, const float& d_time)
{

	auto this_abl = dynamics.conveyor.begin();
	auto this_map = dynamics.conveyor_map.begin();

/////////////////////////////////////////ABILITY TO WALLS//////////////////////////////////////////

	//Let's check are the ability hit the LEFT wall?
	auto out_of_Lwall = [&](const sf::Sprite& test)
	{
		return (test.getGlobalBounds().left < GFIELD_LEFT);
	};
	this_abl = std::ranges::find_if(dynamics.conveyor, out_of_Lwall);

	//If find one that hit the LEFT wall
	if (this_abl != dynamics.conveyor.end())
	{
		this_map = dynamics.conveyor_map.begin() + (this_abl - dynamics.conveyor.begin());
		
		//Bounce thru X acis
		(*this_abl).setPosition(sf::Vector2f(to_f(GFIELD_LEFT), (*this_abl).getGlobalBounds().top));

		//Invert speed_X, acceleration_X and bounce them
		(*this_map).kinematics.at(V_X) *= (-1.f) * Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(V_Y) *= Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(A_X) *= (-1.f) * Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(A_Y) *= Game::dynamicUnits::abl_bounce;

		//Immidiately re-calculate kinematics
		recalculateAblKinematics((*this_map).kinematics, d_time);

		//And move ability
		(*this_abl).move(sf::Vector2f((*this_map).kinematics.at(DELTA_X), (*this_map).kinematics.at(DELTA_Y)));
	}

	//Let's check are the ability hit the RIGHT wall?
	auto out_of_Rwall = [&](const sf::Sprite& test)
	{
		return ( (test.getGlobalBounds().left + test.getGlobalBounds().width) > GFIELD_RIGHT);
	};
	this_abl = std::ranges::find_if(dynamics.conveyor, out_of_Rwall);

	//If find one that hit the LEFT wall
	if (this_abl != dynamics.conveyor.end())
	{
		this_map = dynamics.conveyor_map.begin() + (this_abl - dynamics.conveyor.begin());

		//Bounce thru X acis
		(*this_abl).setPosition(sf::Vector2f(GFIELD_RIGHT - (*this_abl).getGlobalBounds().width, (*this_abl).getGlobalBounds().top));

		//Invert speed_X, acceleration_X and bounce them
		(*this_map).kinematics.at(V_X) *= (-1.f) * Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(V_Y) *= Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(A_X) *= (-1.f) * Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(A_Y) *= Game::dynamicUnits::abl_bounce;

		//Immidiately re-calculate kinematics
		recalculateAblKinematics((*this_map).kinematics, d_time);

		//And move ability
		(*this_abl).move(sf::Vector2f((*this_map).kinematics.at(DELTA_X), (*this_map).kinematics.at(DELTA_Y)));
	}

	//Let's check are the ability hit the CEILING?
	auto out_of_Ceil = [&](const sf::Sprite& test)
	{
		return (test.getGlobalBounds().top < GFIELD_TOP);
	};
	this_abl = std::ranges::find_if(dynamics.conveyor, out_of_Ceil);

	//If find one that hit the CEILING
	if (this_abl != dynamics.conveyor.end())
	{
		this_map = dynamics.conveyor_map.begin() + (this_abl - dynamics.conveyor.begin());

		//Bounce thru Y acis
		(*this_abl).setPosition(sf::Vector2f((*this_abl).getGlobalBounds().left, to_f(GFIELD_TOP)));

		//Invert speed_Y, acceleration_Y and bounce them
		(*this_map).kinematics.at(V_X) *= Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(V_Y) *= (-1.f) * Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(A_X) *= Game::dynamicUnits::abl_bounce;
		(*this_map).kinematics.at(A_Y) *= (-1.f) * Game::dynamicUnits::abl_bounce;

		//Immidiately re-calculate kinematics
		recalculateAblKinematics((*this_map).kinematics, d_time);

		//And move ability
		(*this_abl).move(sf::Vector2f((*this_map).kinematics.at(DELTA_X), (*this_map).kinematics.at(DELTA_Y)));
	}

//////////////////////////////////////////////LOST ABILITIES///////////////////////////////////////////////

	//Let's check are the ability lost?
	auto out_of_field = [&](const sf::Sprite& test)
	{
		return (test.getGlobalBounds().top >= (GFIELD_BOTTOM + game_field.empty_thk));
	};

	//Go thru all conveyor units
	this_abl = std::ranges::find_if(dynamics.conveyor, out_of_field);

	if (this_abl != dynamics.conveyor.end())
	{
		auto erase_this_map = dynamics.conveyor_map.begin() + (this_abl - dynamics.conveyor.begin());

		dynamics.conveyor_map.erase(erase_this_map);
		dynamics.conveyor.erase(this_abl);

	}
}

inline static void ballHitBlocks(Game::dynamicUnits& dynamics, const float& d_time)
{

/////////////////////////////////////BALL VS BLOCKS//////////////////////////////////////////

	//First of all, let's go out from this function if ball are bellow the BELT
	if (BALL_TOP > FIRST_BLOCK_BOTTOM)
		return;
	
	///<---ASERTION
	//Make sure containers are now the same size
	assert(dynamics.conveyor.size() == dynamics.conveyor_map.size());
	///<---ASERTION

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
	
	auto attacked_unit = dynamics.conveyor.begin();
	auto give_block = dynamics.conveyor_map.begin();
	//Find next block
	give_block = std::ranges::find_if(give_block, dynamics.conveyor_map.end(), only_blocks);

	//If it's not the end of the conveyor - LOOP
	while (give_block != dynamics.conveyor_map.end())
	{
		//Attach to the block unit
		attacked_unit = dynamics.conveyor.begin() + (give_block - dynamics.conveyor_map.begin());

		//Now find unit with collision to it
		attacked_unit = std::ranges::find_if(attacked_unit, dynamics.conveyor.end(), bounds_collision);
		//Attach to the map at this position
		give_block = dynamics.conveyor_map.begin() + (attacked_unit - dynamics.conveyor.begin());
		
		//If it's a block again we can break the LOOP
		if ((give_block != dynamics.conveyor_map.end()) && ((*give_block).block))
		{
			break;
		}
		//If we reach the end: terminate LOOP
		else break;

		//This was the last conveyor unit, break LOOP
		if (give_block == (dynamics.conveyor_map.end() - 1))
		{
			give_block = dynamics.conveyor_map.end();// move to the end, nothing to look anymore
			break;
		}
		
		//If not: find next block
		give_block = std::ranges::find_if(give_block + 1, dynamics.conveyor_map.end(), only_blocks);
	}

	//We didn't reach the end of the conveyor
	//We will collide with ONLY ONE BLOCK
	if ( (attacked_unit != dynamics.conveyor.end()) && (give_block != dynamics.conveyor_map.end()) && ((*give_block).block) )
	{
		///<---ASERTION
		//Make iterators points to the same positions
		assert((attacked_unit - dynamics.conveyor.begin()) == (give_block - dynamics.conveyor_map.begin()));
		///<---ASERTION
		
		//If it is a corner
		if (
			(BALL_UL_CORNER || BALL_BL_CORNER || BALL_UR_CORNER || BALL_BR_CORNER)
			)
		{
			colission_detection col_status{};

			if (BALL_UL_CORNER)
			{
				col_status = checkCornerCollision(ABLOCK_LEFT, ABLOCK_TOP, BALL_OX, BALL_OY, BALL_RAD, BALL_DY);
			}
			else if (BALL_BL_CORNER)
			{
				col_status = checkCornerCollision(ABLOCK_LEFT, ABLOCK_BOTTOM, BALL_OX, BALL_OY, BALL_RAD, BALL_DY);
			}
			else if (BALL_UR_CORNER)
			{
				col_status = checkCornerCollision(ABLOCK_RIGHT, ABLOCK_TOP, BALL_OX, BALL_OY, BALL_RAD, BALL_DY);
			}
			else if (BALL_BR_CORNER)
			{
				col_status = checkCornerCollision(ABLOCK_RIGHT, ABLOCK_BOTTOM, BALL_OX, BALL_OY, BALL_RAD, BALL_DY);
			}

			//Now we got the new position for the ball
			dynamics.ball->setPosition(sf::Vector2f(col_status.vector.x, col_status.vector.y));

			//IMPORTANT thing: kinematics should be swaped
			//Velocities
			std::swap(BALL_VX, BALL_VY);
			//Accelerations
			std::swap(BALL_AX, BALL_AY);

			//Bounce velocities
			BALL_VX *= Game::dynamicUnits::bll_bounce;
			BALL_VY *= Game::dynamicUnits::bll_bounce;

		}
		//If is a flat surface
		else
		{
			if (BALL_L_SIDE)
			{
				//Set ball center ouside bound of the block
				dynamics.ball->setPosition(sf::Vector2f(ABLOCK_LEFT - BALL_RAD, BALL_OY));
				//Bounce velocities
				BALL_VX *= -Game::dynamicUnits::bll_bounce;
				BALL_VY *= Game::dynamicUnits::bll_bounce;
				//Bounce accelerations
				BALL_AX *= -1.f;
				BALL_AY *= 1.f;
			}
			else if (BALL_R_SIDE)
			{
				//Set ball center ouside bound of the block
				dynamics.ball->setPosition(sf::Vector2f(ABLOCK_RIGHT + BALL_RAD, BALL_OY));
				//Bounce velocities
				BALL_VX *= -Game::dynamicUnits::bll_bounce;
				BALL_VY *= Game::dynamicUnits::bll_bounce;
				//Bounce accelerations
				BALL_AX *= -1.f;
				BALL_AY *= 1.f;
			}
			else if (BALL_T_SIDE)
			{
				//Set ball center ouside bound of the block
				dynamics.ball->setPosition(sf::Vector2f(BALL_OX, ABLOCK_TOP - BALL_RAD));
				//Bounce velocities
				BALL_VX *= Game::dynamicUnits::bll_bounce;
				BALL_VY *= -Game::dynamicUnits::bll_bounce;
				//Bounce accelerations
				BALL_AX *= 1.f;
				BALL_AY *= -1.f;
			}
			else if (BALL_B_SIDE)
			{
				//Set ball center ouside bound of the block
				dynamics.ball->setPosition(sf::Vector2f(BALL_OX, ABLOCK_BOTTOM + BALL_RAD));
				//Bounce velocities
				BALL_VX *= Game::dynamicUnits::bll_bounce;
				BALL_VY *= -Game::dynamicUnits::bll_bounce;
				//Bounce accelerations
				BALL_AX *= 1.f;
				BALL_AY *= -1.f;
			}
		}

		//Immidiately do the kinematics recalculations
		recalculate2DKinematics(dynamics.ball_kinematics, d_time);

		//And move
		dynamics.ball->move(sf::Vector2f(BALL_DX, BALL_DY));

		//Choose function to execute
		executor do_this{ (*give_block).function};

		//Pass variable to that function
		do_this( (*give_block).operand );

		//Erase conveyor unit and map to it			
		dynamics.conveyor_map.erase(give_block);
		dynamics.conveyor.erase(attacked_unit);
	}

}

inline static void ballHitAbilities(Game::dynamicUnits& dynamics, const float& d_time)
{

/////////////////////////////////////BALL VS ABILITIES//////////////////////////////////////////

	//First of all, let's go out from this function if ball are bellow the BELT
	//if (BALL_TOP > FIRST_BLOCK_BOTTOM)
	//	return;

	///<---ASERTION
	//Make sure containers are now the same size
	assert(dynamics.conveyor.size() == dynamics.conveyor_map.size());
	///<---ASERTION

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

	auto attacked_unit = dynamics.conveyor.begin();
	auto give_ability = dynamics.conveyor_map.begin();
	//Find next ability
	give_ability = std::ranges::find_if_not(give_ability, dynamics.conveyor_map.end(), only_blocks);

	//If it's not the end of the conveyor - LOOP
	while (give_ability != dynamics.conveyor_map.end())
	{
		//Attach to the ability unit
		attacked_unit = dynamics.conveyor.begin() + (give_ability - dynamics.conveyor_map.begin());

		//Now find unit with collision to it
		attacked_unit = std::ranges::find_if(attacked_unit, dynamics.conveyor.end(), bounds_collision);
		//Attach to the map at this position
		give_ability = dynamics.conveyor_map.begin() + (attacked_unit - dynamics.conveyor.begin());

		//If we not reach the end, we can check if it's an ability
		//AND
		//If it's an ability again we can break the LOOP
		if ((attacked_unit != dynamics.conveyor.end()) && !((*give_ability).block))
		{
			break;
		}
		//If we reach the end: terminate LOOP
		else break;

		//This was the last conveyor unit, break LOOP
		if (give_ability == (dynamics.conveyor_map.end() - 1))
		{
			give_ability = dynamics.conveyor_map.end();// move to the end, nothing to look anymore
			break;
		}

		//If not: find next block
		give_ability = std::ranges::find_if_not(give_ability + 1, dynamics.conveyor_map.end(), only_blocks);
	}

	//We didn't reach the end of the conveyor
	//We will collide with ONLY ONE ABILITY
	if ( (attacked_unit != dynamics.conveyor.end()) && (give_ability != dynamics.conveyor_map.end()) && !((*give_ability).block) )
	{

		///<---ASERTION
		//Make iterators points to the same positions
		assert((attacked_unit - dynamics.conveyor.begin()) == (give_ability - dynamics.conveyor_map.begin()));
		///<---ASERTION

		//If it is a circle collision
		if ((BALL_OX < AABL_RX_LEFT) || (BALL_OX > AABL_RX_RIGHT))
		{
			colission_detection abl_result;

			//From the RIGHT side of the ABILITY
			if (BALL_RIGHT > AABL_LEFT)
			{
				abl_result = checkCircleCollision
				(
					AABL_RX_RIGHT, AABL_Y_CENTER, AABL_RAD,
					BALL_OX, BALL_OY, BALL_RAD, BALL_DY
				);
			}
			//From the LEFT side of the ABILITY
			else
			{
				abl_result = checkCircleCollision
				(
					AABL_RX_LEFT, AABL_Y_CENTER, AABL_RAD,
					BALL_OX, BALL_OY, BALL_RAD, BALL_DY
				);
			}

			if (abl_result.diagnose)
			{
				//Move the ball
				dynamics.ball->move(abl_result.vector);

				//And ability should move in the same way, but invertly
				(*attacked_unit).move(sf::Vector2f( -abl_result.vector.x, -abl_result.vector.y));

				///////////////////RECALCULATE ABILITY KINEMATICS///////////////////////

				(*give_ability).kinematics.at(V_X) += 0.1f * bll(V_X);
				(*give_ability).kinematics.at(V_Y) += 0.1f * bll(V_Y);
				(*give_ability).kinematics.at(A_X) += 0.1f * bll(A_X);
				(*give_ability).kinematics.at(A_Y) += 0.1f * bll(A_Y);

				///////////////////RECALCULATE BALL KINEMATICS///////////////////////

				//X axis acceleration will be inverted
				bll(A_X) *= -1.f;
				bll(A_Y) *= -1.f;

				//Bouncing from the wall
				bll(V_X) *= -Game::dynamicUnits::bll_bounce;
				bll(V_Y) *= -Game::dynamicUnits::bll_bounce;

				//Immidiately do the kinematics recalculations
				recalculate2DKinematics(dynamics.ball_kinematics, d_time);
			}
		}
		//If it is a flat collision
		else
		{
			if (BALL_T_SIDE)
			{
				//Set ball center ouside bound of the block
				dynamics.ball->setPosition(sf::Vector2f(BALL_OX, ABLOCK_TOP - BALL_RAD));

				///////////////////RECALCULATE ABILITY KINEMATICS///////////////////////

				(*give_ability).kinematics.at(V_X) += 0.1f * bll(V_X);
				(*give_ability).kinematics.at(V_Y) += 0.1f * bll(V_Y);
				(*give_ability).kinematics.at(A_X) += 0.1f * bll(A_X);
				(*give_ability).kinematics.at(A_Y) += 0.1f * bll(A_Y);

				///////////////////RECALCULATE BALL KINEMATICS///////////////////////

				//Bounce velocities
				BALL_VX *= Game::dynamicUnits::bll_bounce;
				BALL_VY *= -Game::dynamicUnits::bll_bounce;
				//Bounce accelerations
				BALL_AX *= 1.f;
				BALL_AY *= -1.f;

				//Immidiately do the kinematics recalculations
				recalculate2DKinematics(dynamics.ball_kinematics, d_time);
			}
			else if (BALL_B_SIDE)
			{
				//Set ball center ouside bound of the block
				dynamics.ball->setPosition(sf::Vector2f(BALL_OX, ABLOCK_BOTTOM + BALL_RAD));

				///////////////////RECALCULATE ABILITY KINEMATICS///////////////////////

				(*give_ability).kinematics.at(V_X) += 0.1f * bll(V_X);
				(*give_ability).kinematics.at(V_Y) += 0.1f * bll(V_Y);
				(*give_ability).kinematics.at(A_X) += 0.1f * bll(A_X);
				(*give_ability).kinematics.at(A_Y) += 0.1f * bll(A_Y);

				///////////////////RECALCULATE BALL KINEMATICS///////////////////////

				//Bounce velocities
				BALL_VX *= Game::dynamicUnits::bll_bounce;
				BALL_VY *= -Game::dynamicUnits::bll_bounce;
				//Bounce accelerations
				BALL_AX *= 1.f;
				BALL_AY *= -1.f;

				//Immidiately do the kinematics recalculations
				recalculate2DKinematics(dynamics.ball_kinematics, d_time);
			}
		}
	}
}

inline static void ablHitBlocks(Game::dynamicUnits& dynamics, const float& d_time)
{

/////////////////////////////////////ABILITY VS BLOCKS//////////////////////////////////////////

	///<---ASSERTION
	//Make sure containers are now the same size
	assert(dynamics.conveyor.size() == dynamics.conveyor_map.size());
	///<---ASSERTION

	auto this_unit = dynamics.conveyor.begin();
	auto this_map = dynamics.conveyor_map.begin();
	auto attacked_unit = dynamics.conveyor.begin();
	auto give_block = dynamics.conveyor_map.begin();

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
			(U_HOR_TOUCH(THIS_ABL_LEFT) && (U_VER_TOUCH(THIS_ABL_TOP) || U_VER_TOUCH(THIS_ABL_BOTTOM)))
			||
			(U_HOR_TOUCH(THIS_ABL_RIGHT) && (U_VER_TOUCH(THIS_ABL_TOP) || U_VER_TOUCH(THIS_ABL_BOTTOM)))
			);
	};

	//Make sure it is a ABILITY
	this_map = std::ranges::find_if_not(dynamics.conveyor_map, only_blocks);
	//Find the first ABILITY
	this_unit = dynamics.conveyor.begin() + (this_map - dynamics.conveyor_map.begin());

	//Check if first ABILITY collide some BLOCK, then move to the next one
	while (this_unit != dynamics.conveyor.end())
	{
		//Reset attacking unit
		attacked_unit = dynamics.conveyor.begin();

		//Find first BLOCK after the map
		give_block = std::ranges::find_if(dynamics.conveyor_map, only_blocks);

		//if (give_block == this_map)
			//give_block = std::ranges::find_if_not(give_block + 1, dynamics.conveyor_map.end(), only_blocks);

		if (give_block != dynamics.conveyor_map.end())
		{
			//Attach to the ABILITY unit
			attacked_unit = dynamics.conveyor.begin() + (give_block - dynamics.conveyor_map.begin());
		}
		else attacked_unit = dynamics.conveyor.end();

		//If it's not the end of the conveyor - LOOP
		for (; attacked_unit != dynamics.conveyor.end(); )
		{

			//Now find unit with collision to it
			attacked_unit = std::ranges::find_if(attacked_unit, dynamics.conveyor.end(), bounds_collision);

			//if (attacked_unit == this_unit) attacked_unit = std::ranges::find_if(attacked_unit + 1, dynamics.conveyor.end(), bounds_collision);

			//Attach to the map at this position
			give_block = dynamics.conveyor_map.begin() + (attacked_unit - dynamics.conveyor.begin());

			//If we not reach the end, we can check if it's an ability
			//AND
			//If it's an ability again we can break the LOOP
			if ((attacked_unit != dynamics.conveyor.end()) && ((*give_block).block))
			{
				//CALCULATE COLLISION

				//If it is a corner
				if (
					(THIS_ABL_UL_CORNER || THIS_ABL_BL_CORNER || THIS_ABL_UR_CORNER || THIS_ABL_BR_CORNER)
					)
				{
					colission_detection col_status{};

					if (THIS_ABL_UL_CORNER)
					{
						col_status = checkCornerCollision(ABLOCK_LEFT, ABLOCK_TOP, THIS_ABL_RX_RIGHT, THIS_ABL_Y_CENTER, THIS_ABL_RAD, THIS_MAP_DY);
						col_status.vector.x -= ABLOCK_LEFT;
						col_status.vector.y -= ABLOCK_TOP;
						//Now we got the new position for the ball
						(*this_unit).setPosition(sf::Vector2f(ABLOCK_LEFT - THIS_ABL_WIDTH, THIS_ABL_TOP));
					}
					else if (THIS_ABL_BL_CORNER)
					{
						col_status = checkCornerCollision(ABLOCK_LEFT, ABLOCK_BOTTOM, THIS_ABL_RX_RIGHT, THIS_ABL_Y_CENTER, THIS_ABL_RAD, THIS_MAP_DY);
						col_status.vector.x -= ABLOCK_LEFT;
						col_status.vector.y -= ABLOCK_BOTTOM;
						//Now we got the new position for the ball
						(*this_unit).setPosition(sf::Vector2f(ABLOCK_LEFT - THIS_ABL_WIDTH, THIS_ABL_TOP));
					}
					else if (THIS_ABL_UR_CORNER)
					{
						col_status = checkCornerCollision(ABLOCK_RIGHT, ABLOCK_TOP, THIS_ABL_RX_LEFT, THIS_ABL_Y_CENTER, THIS_ABL_RAD, THIS_MAP_DY);
						col_status.vector.x -= ABLOCK_RIGHT;
						col_status.vector.y -= ABLOCK_TOP;
						//Now we got the new position for the ball
						(*this_unit).setPosition(sf::Vector2f(ABLOCK_RIGHT, THIS_ABL_TOP));
					}
					else if (THIS_ABL_BR_CORNER)
					{
						col_status = checkCornerCollision(ABLOCK_RIGHT, ABLOCK_BOTTOM, THIS_ABL_RX_LEFT, THIS_ABL_Y_CENTER, THIS_ABL_RAD, THIS_MAP_DY);
						col_status.vector.x -= ABLOCK_RIGHT;
						col_status.vector.y -= ABLOCK_BOTTOM;
						//Now we got the new position for the ball
						(*this_unit).setPosition(sf::Vector2f(ABLOCK_RIGHT, THIS_ABL_TOP));
					}

					//IMPORTANT thing: kinematics should be swaped
					//Velocities
					std::swap(THIS_MAP_VX, THIS_MAP_VY);
					//Accelerations
					std::swap(THIS_MAP_AX, THIS_MAP_AY);

					//Bounce velocities
					THIS_MAP_VX *= Game::dynamicUnits::abl_bounce;
					THIS_MAP_VY *= Game::dynamicUnits::abl_bounce;
					//Bounce accelerations
					//THIS_MAP_AX *= 1.f;
					//THIS_MAP_AY *= -1.f;

				}
				//If is a flat surface
				else
				{
					if (THIS_ABL_L_SIDE)
					{
						
						(*this_unit).setPosition(sf::Vector2f(ABLOCK_LEFT - THIS_ABL_WIDTH, THIS_ABL_TOP));

						//Bounce velocities
						THIS_MAP_VX *= -Game::dynamicUnits::bll_bounce;
						THIS_MAP_VY *= Game::dynamicUnits::bll_bounce;
						//Bounce accelerations
						THIS_MAP_AX *= -1.f;
						THIS_MAP_AY *= 1.f;
					}
					else if (THIS_ABL_R_SIDE)
					{

						(*this_unit).setPosition(sf::Vector2f(ABLOCK_RIGHT, THIS_ABL_TOP));

						//Bounce velocities
						THIS_MAP_VX *= -Game::dynamicUnits::bll_bounce;
						THIS_MAP_VY *= Game::dynamicUnits::bll_bounce;
						//Bounce accelerations
						THIS_MAP_AX *= -1.f;
						THIS_MAP_AY *= 1.f;
					}
					else if (THIS_ABL_T_SIDE)
					{

						(*this_unit).setPosition(sf::Vector2f(THIS_ABL_LEFT, ABLOCK_TOP - THIS_ABL_HEIGHT));
						
						//Bounce velocities
						THIS_MAP_VX *= Game::dynamicUnits::abl_bounce;
						THIS_MAP_VY *= -Game::dynamicUnits::abl_bounce;
						//Bounce accelerations
						THIS_MAP_AX *= 1.f;
						THIS_MAP_AY *= -1.f;
					}
					else if (THIS_ABL_B_SIDE)
					{
						
						(*this_unit).setPosition(sf::Vector2f(THIS_ABL_LEFT, ABLOCK_BOTTOM));

						//Bounce velocities
						THIS_MAP_VX *= Game::dynamicUnits::abl_bounce;
						THIS_MAP_VY *= -Game::dynamicUnits::abl_bounce;
						//Bounce accelerations
						THIS_MAP_AX *= 1.f;
						THIS_MAP_AY *= -1.f;
					}
				}

				/////////////////////RECALCULATE THIS ABILITY KINEMATICS/////////////////////////

			}
			
			//If we reach the end: terminate LOOP
			else if (attacked_unit == dynamics.conveyor.end()) break;
			//This was the last conveyor unit, break LOOP
			else if (give_block == (dynamics.conveyor_map.end() - 1)) break;

			//If not: find next ABILITY
			give_block = std::ranges::find_if(give_block + 1, dynamics.conveyor_map.end(), only_blocks);
			//Prepair attacked_unit for checking
			attacked_unit = dynamics.conveyor.begin() + (give_block - dynamics.conveyor_map.begin());
		}

		//Find next ability to test
		this_map = std::ranges::find_if_not(this_map + 1, dynamics.conveyor_map.end(), only_blocks);
		//Find the first ability
		this_unit = dynamics.conveyor.begin() + (this_map - dynamics.conveyor_map.begin());
	}
}

inline static void ablHitAbilities(Game::dynamicUnits& dynamics, const float& d_time)
{

/////////////////////////////////////ABILITY VS ABILITIES//////////////////////////////////////////

	///<---ASERTION
	//Make sure containers are now the same size
	assert(dynamics.conveyor.size() == dynamics.conveyor_map.size());
	///<---ASERTION

	auto this_unit = dynamics.conveyor.begin();
	auto this_map = dynamics.conveyor_map.begin();
	auto attacked_unit = dynamics.conveyor.begin();
	auto give_ability = dynamics.conveyor_map.begin();

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
			(U_HOR_TOUCH(THIS_ABL_LEFT) && (U_VER_TOUCH(THIS_ABL_TOP) || U_VER_TOUCH(THIS_ABL_BOTTOM)))
			||
			(U_HOR_TOUCH(THIS_ABL_RIGHT) && (U_VER_TOUCH(THIS_ABL_TOP) || U_VER_TOUCH(THIS_ABL_BOTTOM)))
			);
	};

	//Make sure it is an ability
	this_map = std::ranges::find_if_not(dynamics.conveyor_map, only_blocks);
	//Find the first ability
	this_unit = dynamics.conveyor.begin() + (this_map - dynamics.conveyor_map.begin());

	//Check if first ability collide some another ability, then move to the next one
	while(this_unit != dynamics.conveyor.end())
	{
		//Reset attacking unit
		attacked_unit = dynamics.conveyor.begin();
		
		//Find next ability after the map
		give_ability = std::ranges::find_if_not(dynamics.conveyor_map, only_blocks);
		//if (give_ability == this_map)
			//give_ability = std::ranges::find_if_not(give_ability+1, dynamics.conveyor_map.end(), only_blocks);
		
		if (give_ability != dynamics.conveyor_map.end())
		{
			//Attach to the ABILITY unit
			attacked_unit = dynamics.conveyor.begin() + (give_ability - dynamics.conveyor_map.begin());
		}
		else attacked_unit = dynamics.conveyor.end();

		//If it's not the end of the conveyor - LOOP
		for( ; attacked_unit != dynamics.conveyor.end(); )
		{

			//Now find unit with collision to it
			attacked_unit = std::ranges::find_if(attacked_unit, dynamics.conveyor.end(), bounds_collision);

			//if (attacked_unit == this_unit) attacked_unit = std::ranges::find_if(attacked_unit+1, dynamics.conveyor.end(), bounds_collision);

			//Attach to the map at this position
			give_ability = dynamics.conveyor_map.begin() + (attacked_unit - dynamics.conveyor.begin());

			//If we not reach the end, we can check if it's an ability
			//AND
			//If it's an ability again we can break the LOOP
			if ((attacked_unit != dynamics.conveyor.end()) && !((*give_ability).block))
			{
				//CALCULATE COLLISION

				//If it is a circle collision
				if (
					(THIS_ABL_RX_RIGHT < AABL_RX_LEFT) || (THIS_ABL_RX_LEFT > AABL_RX_RIGHT)
				)
				{
					colission_detection abl_result;

					//From the RIGHT side of the ABILITY
					if (THIS_ABL_RIGHT > AABL_LEFT)
					{
						abl_result = checkCircleCollision
						(
							AABL_RX_RIGHT, AABL_Y_CENTER, AABL_RAD,
							THIS_ABL_RX_LEFT, THIS_ABL_Y_CENTER, THIS_ABL_RAD, THIS_MAP_DY
						);
					}
					//From the LEFT side of the ABILITY
					else
					{
						abl_result = checkCircleCollision
						(
							AABL_RX_LEFT, AABL_Y_CENTER, AABL_RAD,
							THIS_ABL_RX_RIGHT, THIS_ABL_Y_CENTER, THIS_ABL_RAD, THIS_MAP_DY
						);
					}

					if (abl_result.diagnose)
					{
						//Move the ball
						(*this_unit).move(abl_result.vector);

						//And ability should move in the same way, but invertly
						(*attacked_unit).move(sf::Vector2f(-abl_result.vector.x, -abl_result.vector.y));
					}
				}
				//If it is a flat collision
				else
				{
					if (THIS_ABL_T_SIDE)
					{
						//Set ball center ouside bound of the block
						(*this_unit).setPosition(sf::Vector2f(THIS_ABL_LEFT, ABLOCK_TOP - THIS_ABL_HEIGHT));

					}
					else if (THIS_ABL_B_SIDE)
					{
						//Set ball center ouside bound of the block
						(*this_unit).setPosition(sf::Vector2f(THIS_ABL_LEFT, ABLOCK_BOTTOM));
					}
				}

				///////////////////RECALCULATE ATTACKED ABILITY KINEMATICS///////////////////////

				(*give_ability).kinematics.at(V_X) += 0.1f * (*this_map).kinematics.at(V_X);
				(*give_ability).kinematics.at(V_Y) += 0.1f * (*this_map).kinematics.at(V_Y);
				(*give_ability).kinematics.at(A_X) += 0.1f * (*this_map).kinematics.at(A_X);
				(*give_ability).kinematics.at(A_Y) += 0.1f * (*this_map).kinematics.at(A_Y);

				/////////////////////RECALCULATE THIS ABILITY KINEMATICS/////////////////////////

				//X axis acceleration will be inverted
				(*this_map).kinematics.at(A_X) *= -1.f;
				(*this_map).kinematics.at(A_Y) *= -1.f;
				//Bouncing from the wall
				(*this_map).kinematics.at(V_X) *= -Game::dynamicUnits::abl_bounce;
				(*this_map).kinematics.at(V_Y) *= -Game::dynamicUnits::abl_bounce;

			}
			//If we reach the end: terminate LOOP
			else if (attacked_unit == dynamics.conveyor.end()) break;
			//This was the last conveyor unit, break LOOP
			else if (give_ability == (dynamics.conveyor_map.end() - 1)) break;

			//If not: find next ABILITY
			give_ability = std::ranges::find_if_not(give_ability+1, dynamics.conveyor_map.end(), only_blocks);
			//Prepair attacked_unit for checking
			attacked_unit = dynamics.conveyor.begin() + (give_ability - dynamics.conveyor_map.begin());
		}

		//Find next ability to test
		this_map = std::ranges::find_if_not(this_map + 1, dynamics.conveyor_map.end(), only_blocks);
		//Find the first ability
		this_unit = dynamics.conveyor.begin() + (this_map - dynamics.conveyor_map.begin());
	}
}

inline static void throwAbilities(Game::dynamicUnits& dynamics, const float& d_time)
{

/////////////////////////////////ABILITY VS ABILITIES & BLOCKS/////////////////////////////////////

	//BOUNDERS
	float left_coor{};
	float right_coor{};
	float btm_coor{};

	//HOLD STATUS
	bool hold{};  // false: no hold, true: HOLD this ABILITY

	//Go thru all abilities and keep LEFT and RIGHT coordinates
	for (int index{}; index < dynamics.conveyor.size(); index++)
	{
		//if it is a block: go to the next unit
		if (dynamics.conveyor_map.at(index).block)
		{
			continue;
		}

		//When we finally find the ability:

		//Grab bounds
		left_coor	= INDEXER_LEFT;
		right_coor	= INDEXER_RIGHT;
		btm_coor	= INDEXER_BOTTOM;

		hold = false;  // false: no hold, true: HOLD this ABILITY

		//Now let's search a block or ability that could stop it

		//Assuming that ability could hold by only blocks and abilities with index smallest
		//then tested one
		for (int holder_index{}; holder_index < dynamics.conveyor.size(); holder_index++)
		{
			if (holder_index == index) continue;
			
			//now bring bounds of the hold element
			if
			(
				//Ability lay own on some block or ability
				(HOLDER_TOP == btm_coor)
				&&
				(
					//Left side of the ABILITY inside unit bounds
					( (HOLDER_LEFT < left_coor) && (left_coor < HOLDER_RIGHT) )
					||
					//Right side of the ABILITY inside unit bounds
					( (HOLDER_LEFT < right_coor) && (right_coor < HOLDER_RIGHT) )
				)
			)
			{
				//Once we hold ABILITY: we never release it again
				hold = true;
			}
		}

		//So if no holder that catch ability we can release it
		if (!hold)
		{
			
			dynamics.conveyor_map.at(index).kinematics.at(V_Y) = Game::dynamicUnits::abl_V_step;
			recalculateAblKinematics(dynamics.conveyor_map.at(index).kinematics, d_time);
			dynamics.conveyor.at(index).move(sf::Vector2f(dynamics.conveyor_map.at(index).kinematics.at(DELTA_X), dynamics.conveyor_map.at(index).kinematics.at(DELTA_Y)));
		}
		else
		{
			dynamics.conveyor_map.at(index).kinematics.at(V_Y) = 0;
		}
	}
}
