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
//#include "game_objects.hpp"
//#include "intro_window.hpp"


//int WinMain()
int main()
{
	//==================PREPARE UTILITIES___PART ?___===================

	//Because we have included "util.hpp"
	//pointer 'fork_SUnits' to 'Util::staticUnits' class object will initialize
	//access to the utilities. They (Texts, Fonts,...) can't be global, so we initialize them in the main function
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

	while (application_window.isOpen())
	{
		//First start timer update
		Util::Process::resetStartPoint();

	//=============================INTRO PAGE============================

		while (Intro::Process::running)
		{
			//Initialize pointer to object with event property
			std::unique_ptr<Intro::Process> fork_intro = std::make_unique<Intro::Process>();
			
			//Check timer and blink instruction
			Intro::Process::blinkInstruction(*fork_Util_SUnits);

			//Render screen the Intro objects
			fork_intro->render(application_window, *fork_Util_SUnits);

			//Check user inputs
			fork_intro->interact(application_window);

			Util::Process::updateDelta();
			Intro::Process::blink_timer += Util::Process::delta_time;
		}

		//User could close the window, so we shouldn't waste resources on parsing next Texts, Textures, Frames,...
		//if (application_window.isOpen())
		//{

		//}
	}
	
	return 0;
}
