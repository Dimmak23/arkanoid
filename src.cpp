//C++ headers

//API


//SFML headers
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>

//Custom headers
#include "outline.hpp"
#include "util.hpp"
#include "intro_page.hpp"
#include "game_page.hpp"
#include "game_page_statics.hpp"
#include "game_page_process.hpp"
#include "game_page_dynamics.hpp"
//#include "game_objects.hpp"
//#include "intro_window.hpp"


//int WinMain()
int main()
{
	//==================PREPARE UTILITIES___PART ?___===================

	//Because we have included "util.hpp"
	//pointer 'fork_SUnits' to 'Util::staticUnits' class object will initialize
	//access to the utilities. They (Texts, Fonts,...) can't be global, so we initialize them in the main function
	//std::unique_ptr<Util::staticUnits> fork_Util_SUnits = std::make_unique<Util::staticUnits>();
	std::unique_ptr<Util::staticUnits> fork_Util_SUnits = std::make_unique<Util::staticUnits>();


	//Properties frame_begin_time, perfomance_frequancy, frame_end_time, delta_time
	//are visible as well
	//<--- we can calculate time now!


	
	//=========================APPLICATION WINDOW========================

	//=====Opening screen parameters=====

	//Get user screen properties
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	//Specify opening screen ratio
	sf::Vector2u screen_s(outline.overall_width, outline.overall_height);

	//Render APPLICATION WINDOW
	sf::RenderWindow application_window(
		sf::VideoMode(screen_s, desktop.bitsPerPixel),
		"Arkanoid, produced by DimmaK, 17 october 2022, all rights reserved."
	);
	application_window.setFramerateLimit(360);//more then 300 gives good physics

	//First start timer update
	Util::Process::resetStartPoint();
	
	//Initialize pointer to object with texts property
	std::unique_ptr<Intro::staticUnits> fork_Intro_SUnits = std::make_unique<Intro::staticUnits>(*fork_Util_SUnits);
	
	//Initialize pointer to object with event property
	std::unique_ptr<Intro::Process> fork_Intro_Process = std::make_unique<Intro::Process>();

	while (application_window.isOpen())
	{

	//=============================INTRO PAGE============================

		while (Intro::Process::running)
		{
			//Check timer and blink instruction
			Intro::Process::blinkInstruction(*fork_Intro_SUnits);

			//Render screen the Intro objects
			fork_Intro_Process->render(application_window, *fork_Intro_SUnits);

			//Check user inputs
			fork_Intro_Process->interact(application_window);

			Util::Process::updateDelta();
			Intro::Process::blink_timer += Util::Process::delta_time;
		}

		//Release Intro's that we don't need anymore
		fork_Intro_SUnits.reset(nullptr);
		fork_Intro_Process.reset(nullptr);

	//=============================GAME PAGE============================

		//User could close the window, so we shouldn't waste resources on parsing next Texts, Textures, Frames,...
		if (!(application_window.isOpen()))
		{
			break;
		}

		//Initialize pointer to object with static units properties
		std::cout << "Game::staticUnits defined\n";
		std::unique_ptr<Game::staticUnits> fork_Game_SUnits = std::make_unique<Game::staticUnits>(*fork_Util_SUnits);
		//Game::staticUnits fork_Game_SUnits(*fork_Util_SUnits);

		//Declare pointer to object with event property
		std::cout << "Game::Process declared\n";
		std::unique_ptr<Game::Process> fork_Game_Process{ nullptr };

		//Declare pointer to object with dynamic units properties
		std::cout << "Game::dynamicUnits declared\n";
		std::unique_ptr<Game::dynamicUnits> fork_Game_DUnits{ nullptr };

		//Reset start point before the first Game session
		Util::Process::updateDelta();  //new end time, begin time is also the new end time, delta between new end time and old begin time 

		while (Game::Process::running)
		{
			//Declare pointer to object with event property
			std::cout << "Game::Process defined\n";
			fork_Game_Process.reset(new Game::Process());

			//Declare pointer to object with dynamics properties
			std::cout << "Game::dynamicUnits defined\n";
			fork_Game_DUnits.reset(new Game::dynamicUnits(*fork_Game_SUnits, *fork_Util_SUnits));

			//Reset start point before new Game session
			Util::Process::updateDelta();  //new end time, begin time is also the new end time, delta between new end time and old begin time 

			while (Game::Process::running)
			{
				//<-----fork_Game_DUnits->simulate();
				
				//Update paddle width because of the such ability
				fork_Game_DUnits->adjustPaddle();

				//Update cool electric paddle
				fork_Game_DUnits->updateElectricPaddle(*fork_Game_SUnits);
				
				//Check and extend conveyor belt, if time is come
				fork_Game_DUnits->extendConveyor(*fork_Game_SUnits);

				//Update game time interface
				fork_Game_DUnits->updateGTime();

				//<-----fork_Game_DUnits->simulate();
				
				//Render screen the Game static objects
				fork_Game_Process->render(application_window, *fork_Game_SUnits, *fork_Game_DUnits);

				//Check user inputs
				fork_Game_Process->interact(application_window);

				//We need to get new delta time
				Util::Process::updateDelta();  //new end time, begin time is also the new end time, delta between new end time and old begin time 

				//Update game time
				Game::dynamicUnits::game_time += Util::Process::delta_time;

				//Update conveyor belt extender timer
				Game::dynamicUnits::extender_timer -= Util::Process::delta_time;

				//Update paddle changer timer
				Game::dynamicUnits::pdl_upd_timer += Util::Process::delta_time;

			}

		}

	}
	
	return 0;
}
