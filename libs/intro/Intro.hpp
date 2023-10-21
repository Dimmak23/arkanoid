#pragma once

//* C++ STD
#include <memory>

//* SFML
#include <SFML/Graphics/RenderWindow.hpp>

//* Custom headers
#include "Process.hpp"
#include "Statics.hpp"
#include "Utilities.hpp"

namespace Intro
{
	class Page
	{
	public:
		Page(sf::RenderWindow* parent_window,
			 Utilities::StaticUnits* utility_statics);	  //? neeed to grab parent window for rendering
		~Page();

		//* API for application library
		//?
		bool run();

	private:
		//? Let's prevent copying Game object
		Page(const Page&) = delete;
		Page& operator=(const Page&) = delete;

		//^ Methods
		//?
		// bool initialize();

		//^ Members

		//* States

		//* Graphics
		sf::RenderWindow* _parent{ nullptr };

		//* Sound

		//* Supports
		// std::unique_ptr<Util::StaticUnits> _statics {nullptr};

		//* Parts
		std::unique_ptr<Intro::Statics> _statics{ nullptr };
		std::unique_ptr<Intro::Process> _process{ nullptr };

		//* Utilities
		Utilities::StaticUnits* _utility{ nullptr };

		//! Time, not using this currently
		// Utilities::Timer<float, std::milli>* _timer{ nullptr };
		// float _deltaT{};
	};
};	  // namespace Intro
