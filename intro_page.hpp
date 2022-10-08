#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//				THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE INTRO CODE UNITS				//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers


//API


//SFML headers


//Custom headers
#include "util.hpp"


namespace Intro
{
	class Process;
};

class Intro::Process
{
	public:

		static void blinkInstruction(Util::staticUnits& utils);
		
		static inline bool running{ true };
		static inline float blink_timer{};				//instruction to start are blinked
		static inline const float blink_await{0.25f};

		void render(sf::RenderWindow& window, const Util::staticUnits& utils);
		void interact(sf::RenderWindow& window);

	private:
		
		sf::Event event{};  //!NOT SURE IF I NEED ANY NON-STATIC MEMBERS
};

inline void Intro::Process::blinkInstruction(Util::staticUnits& utils)
{
	if (blink_timer > blink_await)
	{
		if(utils.instruction_label.getFillColor() == sf::Color::Yellow)
		{
			utils.instruction_label.setFillColor(sf::Color::Black);
		}
		else
		{
			utils.instruction_label.setFillColor(sf::Color::Yellow);
		}

		blink_timer = 0;
	}
}

inline void Intro::Process::render(sf::RenderWindow& window, const Util::staticUnits& utils)
{
	//Before do anythin: clear screen
	window.clear(sf::Color::Black);
	
	//Draw LOGO
	window.draw(utils.logo_label);
	//Draw INSTRUCTION
	window.draw(utils.instruction_label);

	//Now send drawings to the screen
	window.display();
}

inline void Intro::Process::interact(sf::RenderWindow& window)
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
			//Press enter and winish Intro page
			else if (event.key.code == sf::Keyboard::Enter)
			{
				running = false;
				window.close();
				break;
			}
		}
	}
}
