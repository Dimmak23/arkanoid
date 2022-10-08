#pragma once

//C++ headers
//#include <string>
#include <iostream>

//API
#include <Windows.h>

//SFML headers
#include <SFML/Graphics.hpp>
//#include <SFML/System/Vector2.hpp>

//Custom headers
#include "util.hpp"
#include "outline.hpp"

#define to_float(lvalue) static_cast<float>(lvalue)

//namespace Intro
//{
	static const float blink_time{ 0.25f };
	static float greetings_timer{};
	static bool to_hide{};
	static bool no_play{};

	//static sf::Text logo_text;
	//static sf::Text instruction_to_start;

	static float delta_time{};

	//static void computeLogo(const unsigned int&, const unsigned int&);
	//static void computeInstruction(const unsigned int&, const unsigned int&);

	//static void greet(sf::RenderWindow& window);

//};

//static void Intro::computeLogo(
//				const unsigned int& window_width,
//				const unsigned int& window_height)
//{
//	//=====LOGO SETTINGS=====
//
//	logo_text.setString("(ARKANOID)");
//	logo_text.setFont(logo_font);
//	logo_text.setCharacterSize(80);
//	logo_text.setOrigin(sf::Vector2f(
//		logo_text.getGlobalBounds().width / 2,
//		logo_text.getGlobalBounds().height / 2
//	)
//	);
//	logo_text.setPosition(sf::Vector2f(to_float(window_width / 2), to_float(window_height / 2)));
//	logo_text.setStyle(sf::Text::Bold);
//	logo_text.setFillColor(sf::Color::Blue);
//
//}
//
//static void Intro::computeInstruction(
//	const unsigned int& window_width,
//	const unsigned int& window_height)
//{
//
//	//=====INSTRUCTION TO START SETTINGS=====
//
//	instruction_to_start.setString("Please, press the ENTER key to start the game...");
//	instruction_to_start.setFont(main_font);
//	instruction_to_start.setCharacterSize(14);
//	instruction_to_start.setOrigin(sf::Vector2f(
//		instruction_to_start.getGlobalBounds().width / 2,
//		instruction_to_start.getGlobalBounds().height / 2
//	)
//	);
//	instruction_to_start.setPosition(sf::Vector2f(to_float(window_width / 2), to_float(window_height / 2 + 140.f)));
//	instruction_to_start.setStyle(sf::Text::Bold);
//	instruction_to_start.setFillColor(sf::Color::Black);
//
//}

//static void Intro::greet(sf::RenderWindow& window)
//{
//
//	//Get CPU time
//	LARGE_INTEGER frame_begin_time{};
//	QueryPerformanceCounter(&frame_begin_time); // here we start to calculate time in the CPU units
//
//	float perfomance_frequancy{};
//	{
//		LARGE_INTEGER perf{};
//		QueryPerformanceFrequency(&perf);
//		perfomance_frequancy = static_cast<float>(perf.QuadPart); // this return how mane cycles in one second
//	}
//
//	LARGE_INTEGER frame_end_time{};
//
//	//==========INTRO WINDOW LOOP===========
//
//	while (window.isOpen())
//	{
//
//		sf::Event intro_event{};//!! Usually this line inside game loop, don't see much necassity
//
//		//==========SET BLINKER===========
//
//		greetings_timer += delta_time;
//		if (greetings_timer > blink_time)
//		{
//			if (to_hide)
//			{
//				instruction_to_start.setFillColor(sf::Color::Black);
//				to_hide = false;
//				greetings_timer = 0;
//			}
//			else
//			{
//				instruction_to_start.setFillColor(sf::Color::Yellow);
//				to_hide = true;
//				greetings_timer = 0;
//			}
//		}
//
//		//==========CHECK USER RESPONCE===========
//
//		// check the type of the event...
//		while (window.pollEvent(intro_event))
//		{
//			// game_window closed
//			if (intro_event.type == sf::Event::Closed)
//			{
//				window.close();
//				no_play = true;
//			}
//
//			// key pressed
//			else if (intro_event.type == sf::Event::KeyPressed)
//			{
//				//Need ENTER
//				if (intro_event.key.code == sf::Keyboard::Enter)
//					window.close();
//			}
//
//		}
//
//		//==========RENDER THE INTRO===========
//
//		//Clear screen
//		window.clear(sf::Color::Black);
//
//		// Draw LOGO label
//		window.draw(logo_text);
//
//		// Draw INSTRUCTIONS label
//		window.draw(instruction_to_start);
//
//		//Display everything to the screen
//		window.display();
//
//		//=====TIME RECALCULATION=====
//
//		QueryPerformanceCounter(&frame_end_time);  // here we finish to calculate time in the CPU units
//
//		//static_cast<float>(frame_end_time.QuadPart - frame_begin_time.QuadPart) - this gives you how many cycles were spent on the current frame
//		delta_time = static_cast<float>(frame_end_time.QuadPart - frame_begin_time.QuadPart) / perfomance_frequancy; // time in seconds
//		frame_begin_time = frame_end_time; // here we start to measure delta_time of the new frame
//
//	}
//
//}


//namespace Intro {
//	class Process;
//	enum texts;
//};
//
//enum Intro::texts
//{
//	LOGO = 0,
//	INSTRUCTION
//};
//
//class Intro::Process
//{
//	public:
//		Process(
//				const unsigned int& w,
//				const unsigned int& h
//		):
//			window_width(w),
//			window_height(h)
//		{
//			
//			//=====LOGO SETTINGS=====
//
//			texts_vec.resize(2);
//
//			//logo_text = std::make_unique<sf::Text>("(ARKANOID)", logo_font);
//
//			texts_vec.at(LOGO).setString("(ARKANOID)");
//			texts_vec.at(LOGO).setFont(logo_font);
//			texts_vec.at(LOGO).setCharacterSize(80);
//			texts_vec.at(LOGO).setOrigin(sf::Vector2f(
//				texts_vec.at(LOGO).getGlobalBounds().width / 2,
//				texts_vec.at(LOGO).getGlobalBounds().height / 2
//			)
//			);
//			texts_vec.at(LOGO).setPosition(sf::Vector2f(to_float(window_width / 2), to_float(window_height / 2)));
//			texts_vec.at(LOGO).setStyle(sf::Text::Bold);
//			texts_vec.at(LOGO).setFillColor(sf::Color::Blue);
//
//			//=====INSTRUCTION TO START SETTINGS=====
//
//			//instruction_to_start = std::make_unique<sf::Text>("Please, press the ENTER key to start the game...", main_font);
//
//			texts_vec.at(INSTRUCTION).setString("Please, press the ENTER key to start the game...");
//			texts_vec.at(INSTRUCTION).setFont(main_font);
//			texts_vec.at(INSTRUCTION).setCharacterSize(14);
//			texts_vec.at(INSTRUCTION).setOrigin(sf::Vector2f(
//				texts_vec.at(INSTRUCTION).getGlobalBounds().width / 2,
//				texts_vec.at(INSTRUCTION).getGlobalBounds().height / 2
//			)
//			);
//			texts_vec.at(INSTRUCTION).setPosition(sf::Vector2f(to_float(window_width / 2), to_float(window_height / 2 + 140.f)));
//			texts_vec.at(INSTRUCTION).setStyle(sf::Text::Bold);
//			texts_vec.at(INSTRUCTION).setFillColor(sf::Color::Black);
//
//		}
//
//		//~Process()
//		//{
//		//	logo_text.reset(nullptr);
//		//	instruction_to_start.reset(nullptr);
//		//}
//
//		void greet(sf::RenderWindow& window);
//	
//	public:
//		const unsigned int window_width;
//		const unsigned int window_height;
//
//		const float blink_time{ 0.25f };
//		float greetings_timer{};
//		bool to_hide{};
//		bool no_play{};
//
//		//std::unique_ptr<sf::Text> logo_text {nullptr};
//		//std::unique_ptr<sf::Text> instruction_to_start {nullptr};
//
//		std::vector<sf::Text> texts_vec;
//
//		float delta_time{};
//
//};
