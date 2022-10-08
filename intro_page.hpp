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
	class staticUnits;
	class Process;
};

class Intro::staticUnits
{
	public:

	staticUnits() = default;								//default-constructor declaration
	staticUnits(const Util::staticUnits& utils);			//constructor dependable on 'Util::staticUnits' object declaration
	staticUnits(Intro::staticUnits&& original);				//Move-constructor declaration

	//! REMEMBER: Fonts, Texts, Textures, ContextSettings,...(what else?) - can't be global. They should be someone's property
	sf::Text logo_label;
	sf::Text instruction_label;
};

inline Intro::staticUnits::staticUnits(const Util::staticUnits& utils)
{
	//=====LOGO SETTINGS=====

	Util::initialize_text(
		logo_label,
		"(ARKANOID)",
		utils.logo_font,
		80,
		true,
		to_f(outline.overall_width / 2),				//Position depend on the one that we have set up in the outline
		to_f(outline.overall_height / 2),				//Position depend on the one that we have set up in the outline
		sf::Text::Bold,
		sf::Color::Blue
	);

	//=====INSTRUCTION TO START SETTINGS=====

	Util::initialize_text(
		instruction_label,
		"Please, press the ENTER key to start the game...",
		utils.main_font,
		14,
		true,
		to_f(outline.overall_width / 2),				//Position depend on the one that we have set up in the outline
		to_f(outline.overall_height / 2 + 140),		//Position depend on the one that we have set up in the outline
		sf::Text::Bold,
		sf::Color::Yellow
	);
}

inline Intro::staticUnits::staticUnits(Intro::staticUnits&& original)
{
	this->logo_label = original.logo_label;
	this->instruction_label = original.instruction_label;

}

class Intro::Process
{
	public:
		
		Process() = default;								//default-constructor declaration
		Process(Intro::Process&& original);				//Move-constructor declaration

		static void blinkInstruction(Intro::staticUnits& utils);
		
		static inline bool running{ true };
		static inline float blink_timer{};				//instruction to start are blinked
		static inline const float blink_await{0.25f};

		void render(sf::RenderWindow& window, const Intro::staticUnits& utils);
		void interact(sf::RenderWindow& window);

	private:
		
		sf::Event event{};  //!NOT SURE IF I NEED ANY NON-STATIC MEMBERS
};

inline Intro::Process::Process(Intro::Process&& original)
{
	this->event = original.event;

}

inline void Intro::Process::blinkInstruction(Intro::staticUnits& utils)
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

inline void Intro::Process::render(sf::RenderWindow& window, const Intro::staticUnits& utils)
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
