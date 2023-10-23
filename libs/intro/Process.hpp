#pragma once

//* C++ STD
#include <iostream>
#include <memory>

//* SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

//* Custom
#include "Statics.hpp"
#include "Utilities.hpp"

namespace Intro
{
	class Process
	{
	public:
		Process(sf::RenderWindow* parent_window);
		~Process();

		// # API
		bool isRunning() const;
		void tickTimer(float tick);
		void blinkInstruction(Intro::Statics& utils);
		void render(const Intro::Statics& utils);
		void interact(sf::RenderWindow& window);

	private:
		//? Let's prevent copying Game object
		Process(const Process&) = delete;
		Process& operator=(const Process&) = delete;

		//^ Methods

	private:
		//^ Members
		sf::RenderWindow* _parent;

		//* Essentials
		sf::Event _event{};

		//* States
		bool _running{ true };

		//* Utilities
		float _blinkTimer{};
		const float _blinkAwait{ 0.25f };
	};
};	  // namespace Intro