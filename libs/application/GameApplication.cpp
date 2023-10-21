#include "GameApplication.hpp"

Arkanoid::GameApplication::GameApplication(int argc, char** argv)
{
	// ? Get desirable window size from command line
	// # argc, argv -> _appWidth, _appHeight{}

	if (!this->initialize()) std::cout << "Couldn't initialize SFML window...\n";
}

Arkanoid::GameApplication::~GameApplication() {}

bool Arkanoid::GameApplication::run()
{
	// Start timer update
	Util::Process::resetStartPoint();

	while (_mainWindow->isOpen())
	{
		//=============================INTRO PAGE============================

		// Hold Intro page until user will respond
		while (Intro::Process::running)
		{
			// Check timer and blink instruction
			Intro::Process::blinkInstruction(*_introStatics);

			// Render screen the Intro objects
			_introProcess->render(*_mainWindow, *_introStatics);

			// Check user inputs
			_introProcess->interact(*_mainWindow);

			Util::Process::updateDelta();
			Intro::Process::blink_timer += Util::Process::delta_time;
		}

		// Release Intro's that we don't need anymore
		_introStatics.reset(nullptr);
		_introProcess.reset(nullptr);

		//=============================GAME PAGE============================

		// User could close the window, so we shouldn't waste resources on parsing next Texts, Textures, Frames,...
		if (!(_mainWindow->isOpen())) break;

		// Initialize pointer to object with static units properties
		_gameplayStatics = std::make_unique<Game::StaticUnits>(*_statics);

		// Reset start point before the first Game session
		Util::Process::updateDelta();	 // new end time, begin time is also the new end time, delta between new end
										 // time and old begin time

		while (Util::Process::running)
		{
			_gameProcess.reset(new Game::Process());

			// std::cout << "&_gameProcess = " << _gameProcess.get() << '\n';
			// std::cout << "Game::Process::running: " << std::boolalpha << Game::Process::running << '\n';

			_gameDynamics.reset(new Game::DynamicUnits(*_gameplayStatics, *_statics));

			// Reset start point before new Game session
			Util::Process::updateDelta();	 // new end time, begin time is also the new end time, delta between new end
											 // time and old begin time

			while (Game::Process::running)
			{
				// User could close the window, so we shouldn't waste resources on processing
				if (!(_mainWindow->isOpen())) break;

				// If game not on the pause
				if (!Game::Process::on_pause)
				{
					//<-----_gameDynamics->simulations();

					simulatePhysics(Util::Process::delta_time);

					//<-----_gameDynamics->simulations();

					//<-----_gameDynamics->collisions();

					collideUnits(*_gameDynamics, Util::Process::delta_time);

					ablHitPlayGround(*_gameDynamics, Util::Process::delta_time);

					ballHitBlocks(*_gameDynamics, Util::Process::delta_time);

					ballHitAbilities(*_gameDynamics, Util::Process::delta_time);

					abilityHitBelt(*_gameDynamics, Util::Process::delta_time);

					if (Game::DynamicUnits::game_time > 0.5f) throwAbilities(*_gameDynamics, Util::Process::delta_time);

					//<-----_gameDynamics->collisions();

					//<-----_gameDynamics->movements();

					moveUnits(*_gameDynamics);

					//<-----_gameDynamics->movements();

					//<-----_gameDynamics->tooling();

					// Check do we need to change waiting time
					_gameDynamics->updateExtAwaitTimer();

					// Check and extend conveyor belt, if time is come
					_gameDynamics->extendConveyor(*_gameplayStatics);

					// Check if we are still holding the ball until user response
					_gameDynamics->holdBall();

					// Check if ball have been lost and we need to reset the ball and paddle
					_gameDynamics->waitForBall();

					// Check too long belt
					_gameDynamics->checkLongBelt();

					//<-----_gameDynamics->tooling();

					//<-----_gameDynamics->interfaces();

					// update score
					_gameDynamics->updateScore();

					// blink adder
					_gameDynamics->blinkScoreAdder();

					// update lifes status
					_gameDynamics->updateLifeBalls(*_gameplayStatics);

					// User could catch some ability, so maybe we need to change paddle texture
					_gameDynamics->resizePaddle(*_gameplayStatics);

					// Update cool electric paddle
					_gameDynamics->updateElectricPaddle(*_gameplayStatics);

					// Update game time interface
					_gameDynamics->updateGTime();

					// Update ball parameters interface
					_gameDynamics->updateParInterface(Game::DynamicUnits::ball_kinematics,
													  _gameDynamics->ball_parameters);

					// Update paddle parameters interface
					_gameDynamics->updateParInterface(Game::DynamicUnits::paddle_kinematics,
													  _gameDynamics->paddle_parameters);

					//<-----_gameDynamics->interfaces();
				}

				// Render screen the Game static objects
				_gameProcess->render(*_mainWindow, *_gameplayStatics, *_gameDynamics);

				// Check user inputs
				_gameProcess->interact(*_mainWindow, *_gameDynamics, Util::Process::delta_time);
				;

				/// TIME IS UPDATING WHEN GAME ON PAUSE
				/// SO WE DON"T END IT UP WITH REALY BEG DELTA WHEN GAME GO FROM PAUSE
				// We need to get new delta time
				Util::Process::updateDelta();	 // new end time, begin time is also the new end time, delta between new
												 // end time and old begin time

				// If game not on the pause
				if (!Game::Process::on_pause)
				{
					///<-----TIMERS

					// Update game time
					Game::DynamicUnits::game_time += Util::Process::delta_time;

					// Update conveyor belt extender timer
					// NOTE: If we have lost ball, we don't wait to extend conveyor belt
					if (!Game::DynamicUnits::lost_ball) Game::DynamicUnits::extender_timer -= Util::Process::delta_time;

					// Update paddle changer timer
					Game::DynamicUnits::pdl_upd_timer += Util::Process::delta_time;

					// Update score adder blink timer
					if (Game::DynamicUnits::score_adder)
						Game::DynamicUnits::score_add_timer += Util::Process::delta_time;

					// if ball was lost, then wait for the new one
					if (Game::DynamicUnits::lost_ball) Game::DynamicUnits::ball_timer += Util::Process::delta_time;

					///<-----TIMERS

					// Check if there is no lifes
					if (!(Game::DynamicUnits::lifes))
					{
						// Reset bool state of the Game process
						Game::Process::running = false;
					}
				}
			}

			//=============================OUTRO PAGE============================
			// Proper reset pointer to object with event property
			// _gameProcess.reset(nullptr);

			// Declare pointer to object with dynamics properties
			// _gameDynamics.reset(nullptr);

			// User could close the window, so we shouldn't waste resources on parsing next Texts, Textures, Frames,...
			if (!(_mainWindow->isOpen()))
			{
				break;
			}

			// Initialize pointer to Outro object with texts property
			// _outroStatics.reset(new Outro::StaticUnits(*_statics));

			// Initialize pointer to Outro object with event property
			// _outroProcess.reset(new Outro::Process());

			// Declare pointer to Outro object with texts property
			// std::unique_ptr<Outro::StaticUnits> _outroStatics{ nullptr };
			_outroStatics = std::make_unique<Outro::StaticUnits>(*_statics);
			// Outro::StaticUnits _outroStatics(*_statics);

			// Declare pointer to Outro object with event property
			// std::unique_ptr<Outro::Process> _outroProcess{ nullptr };
			_outroProcess = std::make_unique<Outro::Process>();
			// Outro::Process _outroProcess;

			// Reset start point before new Game session
			Util::Process::updateDelta();	 // new end time, begin time is also the new end time, delta between new end
											 // time and old begin time

			// Hold Outro page until user will respond
			while (Outro::Process::running)
			{
				// User could close the window, so we shouldn't waste resources on processing
				if (!(_mainWindow->isOpen())) break;

				// Check timer and blink instruction
				Outro::Process::blinkInstruction(*_outroStatics);

				// Render screen the Intro objects
				_outroProcess->render(*_mainWindow, *_outroStatics);

				// Check user inputs
				_outroProcess->interact(*_mainWindow);

				Util::Process::updateDelta();

				Outro::Process::blink_timer += Util::Process::delta_time;
			}

			// Set to the application running status result of the user input
			Util::Process::running = Outro::Process::result;

			// Reset pointer to Outro object with texts property
			_outroStatics.reset(nullptr);

			// Reset pointer to Outro object with event property
			_outroProcess.reset(nullptr);
		}
	}

	//
	_statics.reset(nullptr);

	// Reset pointer to Intro object with texts property
	_introStatics.reset(nullptr);

	// Reset pointer to Intro object with event property
	_introProcess.reset(nullptr);

	return true;
}

bool Arkanoid::GameApplication::initialize()
{
	//=========================PREPARE UTILITIES========================

	// Because we have included "util.hpp"
	// pointer 'fork_SUnits' to 'Util::StaticUnits' class object will initialize
	// access to the utilities. They (Texts, Fonts,...) can't be global, so we initialize them in the main function
	// std::unique_ptr<Util::StaticUnits> fork_Util_SUnits = std::make_unique<Util::StaticUnits>();
	_statics = std::make_unique<Util::StaticUnits>();

	// Properties frame_begin_time, perfomance_frequancy, frame_end_time, delta_time
	// are visible as well
	//<--- we can calculate time now!

	//=========================APPLICATION WINDOW========================

	//=====Opening screen parameters=====

	// ? Get user screen properties
	_desktopMode = sf::VideoMode::getDesktopMode();

	// ? Specify opening screen ratio
	_screenSize = sf::Vector2u(outline.overall_width, outline.overall_height);

	// Render APPLICATION WINDOW
	_mainWindow =
		std::make_unique<sf::RenderWindow>(sf::VideoMode(_screenSize.x, _screenSize.y, _desktopMode.bitsPerPixel),
										   "Arkanoid, produced by DimmaK, 24 october 2022, all rights "
										   "reserved."
										   /// FOR DEPLOY
										   /*,sf::Style::Fullscreen*/
		);
	_mainWindow->setFramerateLimit(360);	// more then 300 gives good physics

	/// FOR DEPLOY ON SMALL SCREENS
	// change the size of the window
	// _mainWindow.setSize(sf::Vector2u(1200, 800));
	// _mainWindow.setPosition(sf::Vector2i(50, 50));  //There is some issue when window oppenning to high

	// Initialize pointer to Intro object with texts property
	_introStatics = std::make_unique<Intro::StaticUnits>(*_statics);

	// Initialize pointer to Intro object with event property
	_introProcess = std::make_unique<Intro::Process>();

	return _mainWindow->isOpen();
}
