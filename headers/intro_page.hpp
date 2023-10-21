// #pragma once

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //										    												                      //
// //										    												                      //
// //				          THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE INTRO CODE UNITS				          //
// //										    												                      //
// //										    												                      //
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// //* C++ STD

// //* SFML

// //* Custom headers
// #include "Utilities.hpp"

// namespace Intro
// {
// 	class StaticUnits;
// 	class Process;
// };	  // namespace Intro

// class Intro::StaticUnits
// {
// public:
// 	StaticUnits() = default;							 // default-constructor declaration
// 	StaticUnits(const Utilities::StaticUnits& utils);	 // constructor dependable on 'Utilities::StaticUnits' object
// 														 // declaration

// 	// These constructors never been called
// 	//! It's good!
// 	StaticUnits(Intro::StaticUnits& original) noexcept;		// Copy-constructor declaration
// 	StaticUnits(Intro::StaticUnits&& original) noexcept;	// Move-constructor declaration

// 	//! REMEMBER: Fonts, Texts, Textures, ContextSettings,...(what else?) - can't be global. They should be someone's
// 	//! property
// 	sf::Text logo_label;
// 	sf::Text instruction_label;
// };

// inline Intro::StaticUnits::StaticUnits(const Utilities::StaticUnits& utils)
// {
// 	//=====LOGO SETTINGS=====

// 	Utilities::initialize_text(
// 		logo_label, "(ARKANOID)", utils.logo_font, 80, true,
// 		to_f(outline.overall_width / 2),	 // Position depend on the one that we have set up in the outline
// 		to_f(outline.overall_height / 2),	 // Position depend on the one that we have set up in the outline
// 		sf::Text::Bold, sf::Color::Blue);

// 	//=====INSTRUCTION TO START SETTINGS=====

// 	Utilities::initialize_text(
// 		instruction_label, "Please, press the ENTER key to start the game...", utils.main_font, 14, true,
// 		to_f(outline.overall_width / 2),		   // Position depend on the one that we have set up in the outline
// 		to_f(outline.overall_height / 2 + 140),	   // Position depend on the one that we have set up in the outline
// 		sf::Text::Bold, sf::Color::Yellow);
// }

// inline Intro::StaticUnits::StaticUnits(Intro::StaticUnits& original) noexcept
// {
// 	std::cout << "Copy constructor 'Intro::StaticUnits' been called...\n";
// 	this->logo_label = original.logo_label;
// 	this->instruction_label = original.instruction_label;
// }

// inline Intro::StaticUnits::StaticUnits(Intro::StaticUnits&& original) noexcept
// {
// 	std::cout << "Move constructor 'Intro::StaticUnits' been called...\n";
// 	this->logo_label = original.logo_label;
// 	this->instruction_label = original.instruction_label;
// }

// class Intro::Process
// {
// public:
// 	Process() = default;	// default-constructor declaration

// 	static void blinkInstruction(Intro::StaticUnits& utils);

// 	static inline bool running{ true };
// 	static inline float blink_timer{};	  // instruction to start are blinked
// 	static inline const float blink_await{ 0.25f };

// 	void render(sf::RenderWindow& window, const Intro::StaticUnits& utils);
// 	void interact(sf::RenderWindow& window);

// private:
// 	sf::Event event{};	  //! NOT SURE IF I NEED ANY NON-STATIC MEMBERS
// };

// inline void Intro::Process::blinkInstruction(Intro::StaticUnits& utils)
// {
// 	if (blink_timer > blink_await)
// 	{
// 		if (utils.instruction_label.getFillColor() == sf::Color::Yellow)
// 		{
// 			utils.instruction_label.setFillColor(sf::Color::Black);
// 		}
// 		else
// 		{
// 			utils.instruction_label.setFillColor(sf::Color::Yellow);
// 		}

// 		blink_timer = 0;
// 	}
// }

// inline void Intro::Process::render(sf::RenderWindow& window, const Intro::StaticUnits& utils)
// {
// 	// Before do anything: clear screen
// 	window.clear(sf::Color::Black);

// 	// Draw LOGO
// 	window.draw(utils.logo_label);
// 	// Draw INSTRUCTION
// 	window.draw(utils.instruction_label);

// 	// Now send drawings to the screen
// 	window.display();
// }

// inline void Intro::Process::interact(sf::RenderWindow& window)
// {
// 	while (window.pollEvent(event))
// 	{
// 		// application_window closed
// 		if (event.type == sf::Event::Closed)
// 		{
// 			running = false;	// also should be here
// 			window.close();
// 			break;
// 		}
// 		else if (event.type == sf::Event::KeyPressed)
// 		{
// 			// Also close by 'Esc' keyboard button
// 			if (event.key.code == sf::Keyboard::Escape)
// 			{
// 				running = false;	// also should be here
// 				window.close();
// 				break;
// 			}
// 			// Press enter and winish Intro page
// 			else if (event.key.code == sf::Keyboard::Enter)
// 			{
// 				running = false;
// 				break;
// 			}
// 		}
// 	}
// }
