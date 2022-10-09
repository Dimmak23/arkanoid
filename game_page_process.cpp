#include "game_page_process.hpp"

void Game::Process::render(sf::RenderWindow& window, const Game::staticUnits& utils)
{
	//Before do anything: clear screen
	window.clear(sf::Color::Black);


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

	for (auto& circle : utils.lifes_outline)
		window.draw(circle);

	for (auto& parameter : utils.ball_parameters)
		window.draw(parameter);

	for (auto& frame : utils.ball_p_frames)
		window.draw(frame);

	for (auto& parameter : utils.paddle_parameters)
		window.draw(parameter);

	for (auto& frame : utils.paddle_p_frames)
		window.draw(frame);

	//Now send drawings to the screen
	window.display();
}

void Game::Process::interact(sf::RenderWindow& window)
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
			//Also close by 'Esc' keyboard button
			if (event.key.code == sf::Keyboard::Escape)
			{
				running = false;  // also should be here
				window.close();
				break;
			}
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