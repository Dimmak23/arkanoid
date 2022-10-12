#include "game_page.hpp"
#include "game_page_statics.hpp"
#include "game_page_dynamics.hpp"
#include "game_page_process.hpp"
#include "game_page_physics.hpp"


//DEFINES
#define paddle(lvalue) Game::dynamicUnits::paddle_kinematics.at(lvalue)
#define ball(lvalue) Game::dynamicUnits::ball_kinematics.at(lvalue)

//METHODS

void Game::Process::render(sf::RenderWindow& window, const Game::staticUnits& utils, const Game::dynamicUnits& dynamo)
{
	//Before do anything: clear screen
	window.clear(sf::Color::Black);

//==================================STATICS===============================

	//===========FRAMES=============

	window.draw(utils.legend_frame);
	window.draw(utils.game_frame);
	window.draw(utils.status_frame);

	//===========LABELS=============

	//LEGEND
	window.draw(utils.blocks_label);
	for (auto& description : utils.blocks_descriptions)
		window.draw(description);

	for (auto& block : utils.blk_sprites)
		window.draw(block);

	window.draw(utils.abilities_label);
	for (auto& description : utils.abilities_descriptions)
		window.draw(description);

	for (auto& ability : utils.abl_sprites)
		window.draw(ability);

	//STATUS
	for (auto& label : utils.status_labels)
		window.draw(label);

	//STATUS LABELS ADDERS
	window.draw(utils.timer_adder);
	window.draw(utils.countdown_adder);

	//LIFES CIRCLES
	for (auto& circle : utils.lifes_outline)
		window.draw(circle);

	for (auto& parameter : utils.ball_parameters)
		window.draw(parameter);

	//BALL STATUS FRAMES
	for (auto& frame : utils.ball_p_frames)
		window.draw(frame);

	for (auto& parameter : utils.paddle_parameters)
		window.draw(parameter);

	//PADDLE STATUS FRAMES
	for (auto& frame : utils.paddle_p_frames)
		window.draw(frame);

//==================================DYNAMICS===============================

	//===========CONVEYOR BELT=============

	for (auto& unit : dynamo.conveyor)
		window.draw((*unit));

	//===========PADDLE=============

	window.draw(*(dynamo.paddle));

	//===========BALL=============

	window.draw(*(dynamo.ball));

	//===========STATUSES=============

	//SCORE
	window.draw(dynamo.score_label);
	window.draw(dynamo.score_add_label);

	//LIFE BALLS
	for (auto& ball : dynamo.lifes_balls)
		window.draw((*ball));

	//GAME TIME
	window.draw(dynamo.game_timer);

	//COUNTDOWN TO THE NEW LINE
	window.draw(dynamo.extender_countdown);

	//KINEMATIC PARAMETERS INTERFACE

	for(auto& parameter: dynamo.ball_parameters)
		window.draw(parameter);

	for(auto& parameter: dynamo.paddle_parameters)
		window.draw(parameter);

//==================================BASEMENT===============================

	//This should help with hiding ball in the textures
	window.draw(dynamo.basement);


//==================================DYNAMICS===============================
	
	//Now send drawings to the screen
	window.display();
}

void Game::Process::interact(sf::RenderWindow& window, Game::dynamicUnits& dynamo, const float& d_time)
{
	while (window.pollEvent(event))
	{
		// application_window closed
		if (event.type == sf::Event::Closed)
		{
			running = false;  // also should be here
			window.close();
			break;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			//paddle(A_X) = 0;


			//Also close by 'Esc' keyboard button
			if (event.key.code == sf::Keyboard::Escape)
			{
				running = false;  // also should be here
				window.close();
				break;
			}

			//LEFT button we use for loosing speed in the X axis
			else if (event.key.code == sf::Keyboard::Left)
			{
				//paddle(V_X) = -Game::dynamicUnits::pdl_V_step;
				paddle(A_X) -= Game::dynamicUnits::pdl_A_step;
			}
			//RIGHT button we use for increasing speed in the X axis
			else if (event.key.code == sf::Keyboard::Right)
			{
				//paddle(V_X) = Game::dynamicUnits::pdl_V_step;
				paddle(A_X) += Game::dynamicUnits::pdl_A_step;
			}

			//paddle(A_X) -= paddle(V_X) * Game::dynamicUnits::pdl_friction;
			//paddle(DELTA_X) = paddle(V_X) * d_time + paddle(A_X) * d_time * d_time / 2.f;
			//paddle(V_X) += paddle(A_X) * d_time;
			
			recalculate1DKinematics(Game::dynamicUnits::paddle_kinematics, Game::dynamicUnits::pdl_friction, d_time);

			dynamo.paddle->move(sf::Vector2f(paddle(DELTA_X), 0));

			////Press enter and winish Intro page
			//else if (event.key.code == sf::Keyboard::Enter)
			//{
			//	running = false;
			//	window.close();
			//	break;
			//}
		}
	}

}