#pragma once

// * C++ STD
#include <memory>

// * SFML
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

// * Custom
#include "game_page.hpp"
#include "game_page_collisions.hpp"
#include "game_page_dynamics.hpp"
#include "game_page_movements.hpp"
#include "game_page_physics.hpp"
#include "game_page_process.hpp"
#include "game_page_statics.hpp"
#include "intro_page.hpp"
#include "outline.hpp"
#include "outro_page.hpp"
#include "util.hpp"

namespace Arkanoid
{
	class GameApplication
	{
	public:
		//? Game can be created only with parameters
		GameApplication() = delete;
		GameApplication(int argc, char** argv);
		//? Destroy resources here
		~GameApplication();

		//* API for main translation unit
		//?
		bool run();

	private:
		// Let's prevent copying Game object
		GameApplication(const GameApplication&) = delete;
		GameApplication& operator=(const GameApplication&) = delete;

		//^ Methods
		//?
		bool initialize();

		//^ Members

		//* States

		//* Graphics
		std::unique_ptr<sf::RenderWindow> _mainWindow{ nullptr };

		//* Sound

		//* Supports
		std::unique_ptr<Util::StaticUnits> _statics;

		//* Pages
		//@ Intro
		std::unique_ptr<Intro::StaticUnits> _introStatics{ nullptr };
		std::unique_ptr<Intro::Process> _introProcess{ nullptr };
		//@ Game
		std::unique_ptr<Game::StaticUnits> _gameplayStatics{ nullptr };
		std::unique_ptr<Game::Process> _gameProcess{ nullptr };
		std::unique_ptr<Game::DynamicUnits> _gameDynamics{ nullptr };
		//@ Outro
		std::unique_ptr<Outro::StaticUnits> _outroStatics{ nullptr };
		std::unique_ptr<Outro::Process> _outroProcess{ nullptr };

		//* Utilities
		sf::VideoMode _desktopMode;
		sf::Vector2u _screenSize;
		unsigned int _appWidth{};	  //! We don't really need to keep this
		unsigned int _appHeight{};	  //! We don't really need to keep this

		//! Time, not using this currently
		// Utilities::Timer<float, std::milli>* _timer{ nullptr };
		// float _deltaT{};
	};

};	  // namespace Arkanoid