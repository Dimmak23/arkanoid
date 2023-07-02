//C++ headers
#include <memory>
#include <Windows.h>

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
#include "game_page_physics.hpp"
#include "game_page_movements.hpp"
#include "game_page_collisions.hpp"

#include "outro_page.hpp"


//=========================================================MAIN================================================================

//int WINAPI WinMain(
//	_In_		HINSTANCE hInstance,
//	//A handle to the current instance of the application.
//	_In_opt_	HINSTANCE hPrevInstance,
//	/*
//	A handle to the previous instance of the application.
//	This parameter is always NULL.
//	If you need to detect whether another instance already exists,
//	create a uniquely named mutex using the CreateMutex function.
//	CreateMutex will succeed even if the mutex already exists,
//	but the function will return ERROR_ALREADY_EXISTS.
//	This indicates that another instance of your application exists,
//	because it created the mutex first. However, a malicious user can create
//	this mutex before you doand prevent your application from starting.
//	To prevent this situation, create a randomly named mutexand store
//	the name so that it can only be obtained by an authorized user.
//	Alternatively, you can use a file for this purpose.
//	To limit your application to one instance per user,
//	create a locked file in the user's profile directory.
//	*/
//	_In_		LPSTR     lpCmdLine,
//	/*
//	The command line for the application, excluding the program name.
//	To retrieve the entire command line, use the GetCommandLine function.
//	*/
//	_In_		int       nShowCmd
//	/*
//	Controls how the window is to be shown.
//	This parameter can be any of the values that can be specified
//	in the nCmdShow parameter for the ShowWindow function.
//	*/
//)
int main()
{
	//=========================PREPARE UTILITIES========================

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
		"Arkanoid, produced by DimmaK, 24 october 2022, all rights reserved."
		///FOR DEPLOY
		/*,sf::Style::Fullscreen*/
	);
	application_window.setFramerateLimit(360);//more then 300 gives good physics

	///FOR DEPLOY ON SMALL SCREENS
	// change the size of the window
	//application_window.setSize(sf::Vector2u(1200, 800));
	//application_window.setPosition(sf::Vector2i(50, 50));  //There is some issue when window oppenning to high
	
	//Initialize pointer to Intro object with texts property
	std::unique_ptr<Intro::staticUnits> fork_Intro_SUnits = std::make_unique<Intro::staticUnits>(*fork_Util_SUnits);
	
	//Initialize pointer to Intro object with event property
	std::unique_ptr<Intro::Process> fork_Intro_Process = std::make_unique<Intro::Process>();
	
	//Start timer update
	Util::Process::resetStartPoint();

	while (application_window.isOpen())
	{

	//=============================INTRO PAGE============================

		//Hold Intro page until user will respond
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
		if (!(application_window.isOpen())) break;

		//Initialize pointer to object with static units properties
		std::unique_ptr<Game::staticUnits> fork_Game_SUnits = std::make_unique<Game::staticUnits>(*fork_Util_SUnits);

		//Declare pointer to object with event property
		std::unique_ptr<Game::Process> fork_Game_Process{ nullptr };

		//Declare pointer to object with dynamic units properties
		std::unique_ptr<Game::dynamicUnits> fork_Game_DUnits{ nullptr };

		//Reset start point before the first Game session
		Util::Process::updateDelta();  //new end time, begin time is also the new end time, delta between new end time and old begin time 

		while (Util::Process::running)
		{
		
			fork_Game_Process.reset(new Game::Process());

			//std::cout << "&fork_Game_Process = " << fork_Game_Process.get() << '\n';
			//std::cout << "Game::Process::running: " << std::boolalpha << Game::Process::running << '\n';

			fork_Game_DUnits.reset(new Game::dynamicUnits(*fork_Game_SUnits, *fork_Util_SUnits));

			//Reset start point before new Game session
			Util::Process::updateDelta();  //new end time, begin time is also the new end time, delta between new end time and old begin time 

			while (Game::Process::running)
			{
				//User could close the window, so we shouldn't waste resources on processing
				if (!(application_window.isOpen())) break;

				//If game not on the pause
				if (!Game::Process::on_pause)
				{
					//<-----fork_Game_DUnits->simulations();

					simulatePhysics(Util::Process::delta_time);

					//<-----fork_Game_DUnits->simulations();





					//<-----fork_Game_DUnits->collisions();

					collideUnits(*fork_Game_DUnits, Util::Process::delta_time);

					ablHitPlayGround(*fork_Game_DUnits, Util::Process::delta_time);

					ballHitBlocks(*fork_Game_DUnits, Util::Process::delta_time);

					ballHitAbilities(*fork_Game_DUnits, Util::Process::delta_time);

					abilityHitBelt(*fork_Game_DUnits, Util::Process::delta_time);

					if (Game::dynamicUnits::game_time > 0.5f) throwAbilities(*fork_Game_DUnits, Util::Process::delta_time);

					//<-----fork_Game_DUnits->collisions();




					//<-----fork_Game_DUnits->movements();

					moveUnits(*fork_Game_DUnits);

					//<-----fork_Game_DUnits->movements();




					//<-----fork_Game_DUnits->tooling();

					//Check do we need to change waiting time
					fork_Game_DUnits->updateExtAwaitTimer();

					//Check and extend conveyor belt, if time is come
					fork_Game_DUnits->extendConveyor(*fork_Game_SUnits);

					//Check if we are still holding the ball until user response
					fork_Game_DUnits->holdBall();

					//Check if ball have been lost and we need to reset the ball and paddle
					fork_Game_DUnits->waitForBall();

					//Check too long belt
					fork_Game_DUnits->checkLongBelt();

					//<-----fork_Game_DUnits->tooling();




					//<-----fork_Game_DUnits->interfaces();

					//update score
					fork_Game_DUnits->updateScore();

					//blink adder
					fork_Game_DUnits->blinkScoreAdder();

					//update lifes status
					fork_Game_DUnits->updateLifeBalls(*fork_Game_SUnits);

					//User could catch some ability, so maybe we need to change paddle texture
					fork_Game_DUnits->resizePaddle(*fork_Game_SUnits);

					//Update cool electric paddle
					fork_Game_DUnits->updateElectricPaddle(*fork_Game_SUnits);

					//Update game time interface
					fork_Game_DUnits->updateGTime();

					//Update ball parameters interface
					fork_Game_DUnits->updateParInterface(Game::dynamicUnits::ball_kinematics, fork_Game_DUnits->ball_parameters);

					//Update paddle parameters interface
					fork_Game_DUnits->updateParInterface(Game::dynamicUnits::paddle_kinematics, fork_Game_DUnits->paddle_parameters);

					//<-----fork_Game_DUnits->interfaces();
				}

				//Render screen the Game static objects
				fork_Game_Process->render(application_window, *fork_Game_SUnits, *fork_Game_DUnits);

				//Check user inputs
				fork_Game_Process->interact(application_window, *fork_Game_DUnits, Util::Process::delta_time);;

				///TIME IS UPDATING WHEN GAME ON PAUSE
				///SO WE DON"T END IT UP WITH REALY BEG DELTA WHEN GAME GO FROM PAUSE
				//We need to get new delta time
				Util::Process::updateDelta();  //new end time, begin time is also the new end time, delta between new end time and old begin time 

				//If game not on the pause
				if(!Game::Process::on_pause)
				{
					
					///<-----TIMERS
					

					//Update game time
					Game::dynamicUnits::game_time += Util::Process::delta_time;

					//Update conveyor belt extender timer
					//NOTE: If we have lost ball, we don't wait to extend conveyor belt
					if (!Game::dynamicUnits::lost_ball) Game::dynamicUnits::extender_timer -= Util::Process::delta_time;

					//Update paddle changer timer
					Game::dynamicUnits::pdl_upd_timer += Util::Process::delta_time;

					//Update score adder blink timer
					if (Game::dynamicUnits::score_adder) Game::dynamicUnits::score_add_timer += Util::Process::delta_time;

					//if ball was lost, then wait for the new one
					if (Game::dynamicUnits::lost_ball) Game::dynamicUnits::ball_timer += Util::Process::delta_time;

					///<-----TIMERS

					//Check if there is no lifes
					if (!(Game::dynamicUnits::lifes))
					{
						//Reset bool state of the Game process
						Game::Process::running = false;
					}
				}

			}
		
			
			//=============================OUTRO PAGE============================
			//Proper reset pointer to object with event property
			//fork_Game_Process.reset(nullptr);

			//Declare pointer to object with dynamics properties
			//fork_Game_DUnits.reset(nullptr);

			//User could close the window, so we shouldn't waste resources on parsing next Texts, Textures, Frames,...
			if (!(application_window.isOpen()))
			{
				break;
			}

			
			//Initialize pointer to Outro object with texts property
			//fork_Outro_SUnits.reset(new Outro::staticUnits(*fork_Util_SUnits));

			//Initialize pointer to Outro object with event property
			//fork_Outro_Process.reset(new Outro::Process());

			//Declare pointer to Outro object with texts property
			//std::unique_ptr<Outro::staticUnits> fork_Outro_SUnits{ nullptr };
			std::unique_ptr<Outro::staticUnits> fork_Outro_SUnits = std::make_unique<Outro::staticUnits>(*fork_Util_SUnits);
			//Outro::staticUnits fork_Outro_SUnits(*fork_Util_SUnits);

			//Declare pointer to Outro object with event property
			//std::unique_ptr<Outro::Process> fork_Outro_Process{ nullptr };
			std::unique_ptr<Outro::Process> fork_Outro_Process = std::make_unique<Outro::Process>();
			//Outro::Process fork_Outro_Process;

			//Reset start point before new Game session
			Util::Process::updateDelta();  //new end time, begin time is also the new end time, delta between new end time and old begin time 

			//Hold Outro page until user will respond
			while (Outro::Process::running)
			{
				//User could close the window, so we shouldn't waste resources on processing
				if (!(application_window.isOpen())) break;
				
				//Check timer and blink instruction
				Outro::Process::blinkInstruction(*fork_Outro_SUnits);

				//Render screen the Intro objects
				fork_Outro_Process->render(application_window, *fork_Outro_SUnits);

				//Check user inputs
				fork_Outro_Process->interact(application_window);

				Util::Process::updateDelta();

				Outro::Process::blink_timer += Util::Process::delta_time;
			}

			//Set to the application running status result of the user input
			Util::Process::running = Outro::Process::result;
			

			//Reset pointer to Outro object with texts property
			fork_Outro_SUnits.reset( nullptr );

			//Reset pointer to Outro object with event property
			fork_Outro_Process.reset( nullptr );

		}
	}

	//
	fork_Util_SUnits.reset(nullptr);

	//Reset pointer to Intro object with texts property
	fork_Intro_SUnits.reset(nullptr);

	//Reset pointer to Intro object with event property
	fork_Intro_Process.reset(nullptr);

	return 0;
}
