#include "game_page.hpp"
#include "game_page_statics.hpp"
#include "game_page_dynamics.hpp"
#include "game_page_process.hpp"
#include "game_page_physics.hpp"


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

	//===========EXTENSION LINES=============

	for (auto& line : utils.extension_lines)
		window.draw(line);

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
	//window.draw(utils.timer_adder);
	//window.draw(utils.countdown_adder);

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
		window.draw(unit);

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

	//AWAIT FOR THE NEW LINE
	window.draw(dynamo.extender_await);

	//KINEMATIC PARAMETERS INTERFACE

	for(auto& parameter: dynamo.ball_parameters)
		window.draw(parameter);

	for(auto& parameter: dynamo.paddle_parameters)
		window.draw(parameter);

//==================================BASEMENT===============================

	//This should help with hiding ball in the textures
	window.draw(dynamo.basement);

//=================================PAUSE PAGE==============================

	//If game on the pause we will see the PAUSE page
	if (on_pause)
	{
		window.draw(dynamo.pause_page);
		window.draw(dynamo.pause_icon);
	}

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
			//Game finished, but don't close window
			//window.close();
			break;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			//INITIATE PAUSE when Esc is pressed
			if (event.key.code == sf::Keyboard::Escape)
			{
				on_pause = true;
				break;
			}
			//DESTROY PAUSE when Space is pressed
			else if (event.key.code == sf::Keyboard::Space)
			{
				//Only if we already on the pause
				if(on_pause) on_pause = false;
				break;
			}

			//If user lost the ball
			//we wait until it appears on the paddle
			//then
			//pressing A: will pass it diagonally - left
			//pressing D: will pass it diagonally - right
			else if (event.key.code == sf::Keyboard::A)
			{
				//Only for the catched ball we can aply
				//such initial impulse
				if (Game::dynamicUnits::catched_ball)
				{
					bll(V_X) -= Game::dynamicUnits::bll_V_step;
					bll(V_Y) -= Game::dynamicUnits::bll_V_step;
					//and reset status, so we don't hold the ball anymore
					Game::dynamicUnits::catched_ball = false;
				}
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				//Only for the catched ball we can aply
				//such initial impulse
				if (Game::dynamicUnits::catched_ball)
				{
					bll(V_X) = Game::dynamicUnits::bll_V_step;
					bll(V_Y) -= Game::dynamicUnits::bll_V_step;
					//and reset status, so we don't hold the ball anymore
					Game::dynamicUnits::catched_ball = false;
				}
			}

			//We can quicly quit by pressing Q
			else if (event.key.code == sf::Keyboard::Q)
			{
				running = false;  // also should be here
				break;
			}

			//LEFT button we use for loosing speed in the X axis
			else if (event.key.code == sf::Keyboard::Left)
			{
				pdl(V_X) -= Game::dynamicUnits::pdl_V_step;
				pdl(A_X) -= Game::dynamicUnits::pdl_A_step;
			}
			//RIGHT button we use for increasing speed in the X axis
			else if (event.key.code == sf::Keyboard::Right)
			{
				pdl(V_X) += Game::dynamicUnits::pdl_V_step;
				pdl(A_X) += Game::dynamicUnits::pdl_A_step;
			}

			recalculate1DKinematics(Game::dynamicUnits::paddle_kinematics, d_time);

			dynamo.paddle->move(sf::Vector2f(pdl(DELTA_X), 0));
		}

	}

}