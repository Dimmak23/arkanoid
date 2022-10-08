//#include "intro_window.hpp"

//void Intro::Process::greet(sf::RenderWindow& window)
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
//				texts_vec.at(INSTRUCTION).setFillColor(sf::Color::Black);
//				to_hide = false;
//				greetings_timer = 0;
//			}
//			else
//			{
//				texts_vec.at(INSTRUCTION).setFillColor(sf::Color::Yellow);
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
//		window.draw(texts_vec.at(LOGO));
//
//		// Draw INSTRUCTIONS label
//		window.draw(texts_vec.at(INSTRUCTION));
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
