#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//				THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE OUTRO CODE UNITS				//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers


//API


//SFML headers
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>


//Custom headers
#include "util.hpp"  //For fonts and other...


namespace Outro
{
	class staticUnits;
	class Process;
};

class Outro::staticUnits
{
	public:

		staticUnits();
		staticUnits(const Util::staticUnits& utils);			//constructor dependable on 'Util::staticUnits' object declaration


		//! REMEMBER: Fonts, Texts, Textures, ContextSettings,...(what else?) - can't be global. They should be someone's property
		sf::Text escape_label;
		sf::Text continue_label;

		sf::Texture game_over_texture;
		sf::Sprite game_over;

	private:

		//Be sure that here we parse independently on the Debug, Release, and USAGE
		//<-
		static inline const std::string gameoverPicPath{ "data/pictures/65-Breakout-Tiles.png" };
		//<-

		static inline const char* gameoverPicParseError{ "_____game over parse error...\n" };
};

inline Outro::staticUnits::staticUnits(const Util::staticUnits& utils)
{
	//=====ESCAPE LABEL SETTINGS=====

	Util::initialize_text(
		escape_label,
		"Press the ESC key to close",
		utils.main_font,
		14,
		true,
		0.f,
		0.f,
		sf::Text::Bold,
		sf::Color::Red
	);

	escape_label.setOrigin(sf::Vector2f(escape_label.getGlobalBounds().width, 0));
	escape_label.setPosition(sf::Vector2f(to_f(outline.overall_width - 20), 20.f));

	//=====INSTRUCTION TO START SETTINGS=====

	Util::initialize_text(
		continue_label,
		"Please, press the ENTER or the SPACE keys to start game over",
		utils.main_font,
		14,
		true,
		0.f,				//Position depend on the one that we have set up in the outline
		0.f,		//Position depend on the one that we have set up in the outline
		sf::Text::Bold,
		sf::Color::Red
	);

	continue_label.setOrigin(sf::Vector2f(continue_label.getGlobalBounds().width / 2, continue_label.getGlobalBounds().height / 2));
	continue_label.setPosition(sf::Vector2f(to_f(outline.overall_width / 2), to_f(outline.overall_height / 2 + 400)));

	//=====GAME OVER PICTURE=====

	Util::safe_parse(game_over_texture, gameoverPicPath,gameoverPicParseError	);

	game_over.setTexture(game_over_texture, true);

	game_over.setScale(sf::Vector2f(to_f(outline.overall_width) / 1024 / 2, to_f(outline.overall_height) / 651 / 2));

	std::cout << "game_over.getGlobalBounds().width = " << game_over.getGlobalBounds().width << '\n';
	std::cout << "game_over.getGlobalBounds().height = " << game_over.getGlobalBounds().height << '\n';

	game_over.setOrigin(sf::Vector2f(game_over.getGlobalBounds().width / 2, game_over.getGlobalBounds().height / 2));

	std::cout << "game_over.getOrigin().x = " << game_over.getOrigin().x << '\n';
	std::cout << "game_over.getOrigin().y = " << game_over.getOrigin().y << '\n';
	std::cout << "game_over.getGlobalBounds().left = " << game_over.getGlobalBounds().left << '\n';
	std::cout << "game_over.getGlobalBounds().top = " << game_over.getGlobalBounds().top << '\n';

	game_over.setPosition(
						sf::Vector2f(
												(to_f(outline.overall_width / 2) - 54.492f),
												(to_f(outline.overall_height / 2) - 23.502f)
											)
	);

	std::cout << "game_over.getGlobalBounds().left = " << game_over.getGlobalBounds().left << '\n';
	std::cout << "game_over.getGlobalBounds().top = " << game_over.getGlobalBounds().top << '\n';

}

class Outro::Process
{
	public:

		Process();

		static void blinkInstruction(Outro::staticUnits& utils);

		static inline bool running{ true };
		static inline bool result{ false };
		static inline float blink_timer{};				//instruction to start are blinked
		static inline const float blink_await{ 0.25f };

		void render(sf::RenderWindow& window, const Outro::staticUnits& utils);
		void interact(sf::RenderWindow& window);

	private:

		sf::Event event{};  //!NOT SURE IF I NEED ANY NON-STATIC MEMBERS
};

inline Outro::Process::Process()
{
	running = true;
	result = false;
	blink_timer = 0.f;
}

inline void Outro::Process::blinkInstruction(Outro::staticUnits& utils)
{
	if (blink_timer > blink_await)
	{
		if (utils.continue_label.getFillColor() == sf::Color::Red)
		{
			utils.continue_label.setFillColor(sf::Color::Black);
		}
		else
		{
			utils.continue_label.setFillColor(sf::Color::Red);
		}

		blink_timer = 0;
	}
}

inline void Outro::Process::render(sf::RenderWindow& window, const Outro::staticUnits& utils)
{
	//Before do anything: clear screen
	window.clear(sf::Color::Black);

	//Draw escape instruction
	window.draw(utils.escape_label);
	//Draw continue instruction
	window.draw(utils.continue_label);
	//Draw game over pic
	window.draw(utils.game_over);

	//Now send drawings to the screen
	window.display();
}

inline void Outro::Process::interact(sf::RenderWindow& window)
{
	while (window.pollEvent(event))
	{
		// application_window closed
		if (event.type == sf::Event::Closed)
		{
			running = false;  // also should be here
			result = true;
			window.close();
			break;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			//Also close by 'Esc' keyboard button
			if (event.key.code == sf::Keyboard::Escape)
			{
				running = false;  // also should be here
				result = false;
				window.close();
				break;
			}
			//Press enter and winish Intro page
			else if ( (event.key.code == sf::Keyboard::Enter) || (event.key.code == sf::Keyboard::Space) )
			{
				running = false;
				result = true;
				break;
			}
		}
	}
}
