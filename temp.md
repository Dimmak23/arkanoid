
//Move somewhere globals
//constexpr unsigned int initWindWidth{ 1800 };
//constexpr unsigned int initWindHeight{ 1210 };
float scale_on_risize_X{};
float scale_on_risize_Y{};

///////////////
//TEMP
///////////////
float d_x{};
float acceleration_x{};
float speed_x{};
const float initial_pos_x{ static_cast<float>(outline.overall_width) / 2.f };
const float initial_pos_y{ static_cast<float>(outline.overall_height) - 20.f };
constexpr float change_paddle_wait{0.025f};

float game_timer{};

//int WinMain()
int main()
{
	//=================PREPARE UTILITIES___PART I___================


	//safe_parse(logo_font, logoFontPath, logoFontParseError);
	//safe_parse(main_font, mainFontPath, mainFontParseError);


	//=====Opening screen parameters=====

	//Get user screen properties
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	//Specify opening screen ratio
	sf::Vector2u screen_s(outline.overall_width, outline.overall_height);
	
	//=========================INTRO WINDOW========================

	//GREETINGS WINDOW
	//Window have to be outside of the class, and inside main() function
	//std::unique_ptr<sf::RenderWindow> intro_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(screen_s, desktop.bitsPerPixel), "Welcome!");
	sf::RenderWindow intro_window(sf::VideoMode(screen_s, desktop.bitsPerPixel), "Welcome!");

	//Pointer to the intro process,
	//creating text labels,
	//asking for user input
	//std::unique_ptr<Intro::Process> GRT = std::make_unique<Intro::Process>(
		//outline.overall_width,
		//outline.overall_height
	//);

	//GRT->greet((*intro_window));
	//Intro::computeLogo(outline.overall_width, outline.overall_height);
	//Intro::computeInstruction(outline.overall_width, outline.overall_height);
	//Intro::greet(intro_window);

	//=====LOGO SETTINGS=====

	sf::Text logo_text;

	logo_text.setString("(ARKANOID)");
	logo_text.setFont(Util::fork_fonts->logo_font);
	logo_text.setCharacterSize(80);
	logo_text.setOrigin(sf::Vector2f(
		logo_text.getGlobalBounds().width / 2,
		logo_text.getGlobalBounds().height / 2
	)
	);
	logo_text.setPosition(sf::Vector2f(to_float(outline.overall_width / 2), to_float(outline.overall_height / 2)));
	logo_text.setStyle(sf::Text::Bold);
	logo_text.setFillColor(sf::Color::Blue);


	//=====INSTRUCTION TO START SETTINGS=====

	//Intro::instruction_to_start.setString("Please, press the ENTER key to start the game...");
	//Intro::instruction_to_start.setFont(main_font);
	//Intro::instruction_to_start.setCharacterSize(14);
	//Intro::instruction_to_start.setOrigin(sf::Vector2f(
	//	Intro::instruction_to_start.getGlobalBounds().width / 2,
	//	Intro::instruction_to_start.getGlobalBounds().height / 2
	//)
	//);
	//Intro::instruction_to_start.setPosition(sf::Vector2f(to_float(outline.overall_width / 2), to_float(outline.overall_height / 2 + 140.f)));
	//Intro::instruction_to_start.setStyle(sf::Text::Bold);
	//Intro::instruction_to_start.setFillColor(sf::Color::Black);


	//Get CPU time
	LARGE_INTEGER fbt{};
	QueryPerformanceCounter(&fbt); // here we start to calculate time in the CPU units

	float pf{};
	{
		LARGE_INTEGER perf{};
		QueryPerformanceFrequency(&perf);
		pf = static_cast<float>(perf.QuadPart); // this return how mane cycles in one second
	}

	LARGE_INTEGER fet{};

	//==========INTRO WINDOW LOOP===========
	
	sf::Event intro_event{};//!! Usually this line inside game loop, don't see much necassity

	while (intro_window.isOpen())
	{


		//==========SET BLINKER===========

		//Intro::greetings_timer += Intro::delta_time;
		//if (Intro::greetings_timer > Intro::blink_time)
		//{
		//	if (Intro::to_hide)
		//	{
		//		Intro::instruction_to_start.setFillColor(sf::Color::Black);
		//		Intro::to_hide = false;
		//		Intro::greetings_timer = 0;
		//	}
		//	else
		//	{
		//		Intro::instruction_to_start.setFillColor(sf::Color::Yellow);
		//		Intro::to_hide = true;
		//		Intro::greetings_timer = 0;
		//	}
		//}

		//==========CHECK USER RESPONCE===========

		// check the type of the event...
		while (intro_window.pollEvent(intro_event))
		{
			// game_window closed
			if (intro_event.type == sf::Event::Closed)
			{
				intro_window.close();
				no_play = true;
			}

			// key pressed
			else if (intro_event.type == sf::Event::KeyPressed)
			{
				//Need ENTER
				if (intro_event.key.code == sf::Keyboard::Enter)
					intro_window.close();
			}

		}

		//==========RENDER THE INTRO===========

		//Clear screen
		intro_window.clear(sf::Color::Black);

		// Draw LOGO label
		intro_window.draw(logo_text);

		// Draw INSTRUCTIONS label
		//intro_window.draw(Intro::instruction_to_start);

		//Display everything to the screen
		intro_window.display();

		//=====TIME RECALCULATION=====

		QueryPerformanceCounter(&fet);  // here we finish to calculate time in the CPU units

		//static_cast<float>(frame_end_time.QuadPart - frame_begin_time.QuadPart) - this gives you how many cycles were spent on the current frame
		delta_time = static_cast<float>(fet.QuadPart - fbt.QuadPart) / pf; // time in seconds
		fbt = fet; // here we start to measure delta_time of the new frame

	}

	//GRT.reset(nullptr);
	//intro_window.reset(nullptr);




	////=========================GAME WINDOW========================

	////desktop.bitsPerPixel --> gets depth of user screen (bits in pixels)
	//sf::RenderWindow game_window(sf::VideoMode(screen_s, desktop.bitsPerPixel), "Arkanoid, produced by DimmaK (c)");
	//game_window.setFramerateLimit(360);//!not sure if any reason in this line

	////=====Render sprites=====

	////Initialize a pointer to game objects
	//std::unique_ptr<GameObjects> dwgs_access = std::make_unique<GameObjects>(280);

	////============================GRID============================

	////===MAIN_FIELD_INIT===

	//sf::RectangleShape game_frame;
	//game_frame.setSize(sf::Vector2f(to_float(game_field.overall_width), to_float(game_field.overall_height)));//Size it
	//game_frame.setOutlineColor(sf::Color::Red);//Color it border
	//game_frame.setFillColor(sf::Color::Black);//Color background
	//game_frame.setOutlineThickness(2);//Set thikness, -<value>: outline inside, +<value>: outline outside
	//game_frame.setPosition(sf::Vector2f(324, 5));

	////==LEGEND_FIELD_INIT==

	//sf::RectangleShape legend_frame;
	//legend_frame.setSize(sf::Vector2f(to_float(legend_field.overall_width), to_float(legend_field.overall_height)));//Size it
	//legend_frame.setOutlineColor(sf::Color::Red);//Color it border
	//legend_frame.setFillColor(sf::Color::Black);//Color background
	//legend_frame.setOutlineThickness(2);//Set thikness, -<value>: outline inside, +<value>: outline outside
	//legend_frame.setPosition(sf::Vector2f(5, 5));

	////==SCORE_FIELD_INIT==

	//sf::RectangleShape status_frame;
	//status_frame.setSize(sf::Vector2f(to_float(status_field.overall_width), to_float(status_field.overall_height)));//Size it
	//status_frame.setOutlineColor(sf::Color::Red);//Color it border
	//status_frame.setFillColor(sf::Color::Black);//Color background
	//status_frame.setOutlineThickness(2);//Set thikness, -<value>: outline inside, +<value>: outline outside
	//status_frame.setPosition(sf::Vector2f(1483, 5));

	////============================TEXTS============================


	////=====SCORE=====



	////sf::Text score_text("Score: ", main_font);
	////score_text.setCharacterSize(20);
	////score_text.setOrigin(sf::Vector2f(0.f, 0.f));
	////score_text.setPosition(sf::Vector2f(1503.f, 20.f));
	//////text.setStyle(sf::Text::Bold);
	////score_text.setFillColor(sf::Color::Red);

	//////test changing text
	////score_text.setString("Score:\n9999\t+100");

	//////=====BALLS=====

	//////Text label for lifes left
	////sf::Text balls_text("Balls: ", main_font);
	////balls_text.setCharacterSize(20);
	////balls_text.setOrigin(sf::Vector2f(0.f, 0.f));
	////balls_text.setPosition(sf::Vector2f(1503.f, 60.f));
	//////text.setStyle(sf::Text::Bold);
	////balls_text.setFillColor(sf::Color::Red);

	//////Life status
	//////Draw balls left



	//////=====TEST_BLOCKS=====

	////float x{ 0.f };
	////float y{ 0.f };

	////const float x_step = 96.f;
	////const float y_step = 32.f;

	////float pos_x{};
	////float pos_y{};

	////sf::Vector2f blocks_scale{ 0.25f, 0.25f };

	////for (int row{}; row < 20; row++)
	////	for (int column{}; column < 14; column++)
	////	{
	////		pos_x = x + static_cast<float>(column) * x_step;
	////		pos_y = y + static_cast<float>(row) * y_step;
	////		dwgs_access->set_position(dwgs_access->blocks.at(column + row * 14), pos_x, pos_y);
	////		std::cout << "Send to screen: [row=" << row << ", column=" << column << ", pos_x=" << pos_x << ", pos_y=" << pos_y << "].\n";
	////	}

	//////=====TEST_ABILITIES=====

	//////set 1 for now
	////dwgs_access->abilities.resize(1);
	//////set in the specific location
	////dwgs_access->abilities.at(0).sprite.setPosition(sf::Vector2f(5.f * x_step, 3.f * y_step));
	//////set defaulted texture
	////dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(EMPTY));
	//////resize
	////dwgs_access->resize_sprite(dwgs_access->abilities.at(0), sf::Vector2f(.393f, .5f));


	//////TESTED BLOCK
	//////dwgs_access->set_position(dwgs_access->blocks.at(3 + 3 * 5), x + static_cast<float>(3+3) * x_step, y + static_cast<float>(3) * y_step);
	//////dwgs_access->set_position(dwgs_access->blocks.at(4 + 2 * 5), x + static_cast<float>(4+1) * x_step, y + static_cast<float>(2) * y_step);

	//////TESTED BALL

	//////set ball in the specific location
	////dwgs_access->ball.sprite.setPosition(sf::Vector2f(7.f * x_step, 6.f * y_step));
	//////set defaulted texture
	////dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(SMALL), true);
	//////resize
	//////dwgs_access->resize_sprite(dwgs_access->ball, sf::Vector2f(.393f, .5f));

	//////TESTED PADDLE

	//////set paddle in the specific location
	////dwgs_access->paddle.sprite.setPosition(sf::Vector2f(static_cast<float>(outline.overall_width) / 2.f, static_cast<float>(outline.overall_height) - 20.f));
	//////set defaulted texture
	////int p_number{ CAPSULE_3 };
	////dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(p_number), true);
	//////set origin to correspond to the setted texture
	////sf::Vector2f tiny_origin(230 / 2.f, 128 / 2.f);
	////sf::Vector2f wide_origin(693 / 2.f, 128 / 2.f);
	////sf::Vector2f capsule_origin(485 / 2.f, 128 / 2.f);
	////sf::Vector2f connector_origin(485 / 2.f, 128 / 2.f);
	////dwgs_access->paddle.sprite.setOrigin(capsule_origin);
	//////Resize
	//////	init scale of the paddle from source
	////sf::Vector2f paddle_scale(.25f, .25f);
	////dwgs_access->resize_sprite(dwgs_access->paddle, paddle_scale);

	////float time_to_change_texture{};




	////==========GAME LOOP==========

	////create an event
	//sf::Event game_event{};//!! Usually this line inside game loop, don't see much necassity


	//float newWindWidth{};
	//float newWindHeight{};

	////==========TIME CALCULATION INIT==========

	////variable to measure how much time is spend on a frame
	//float delta_time{ 0.016666f }; // for the first frame we assume it's gonna be 60 frame/sec

	////Get CPU time
	//LARGE_INTEGER frame_begin_time{};
	//QueryPerformanceCounter(&frame_begin_time); // here we start to calculate time in the CPU units

	//float perfomance_frequancy{};
	//{
	//	LARGE_INTEGER perf{};
	//	QueryPerformanceFrequency(&perf);
	//	perfomance_frequancy = static_cast<float>(perf.QuadPart); // this return how mane cycles in one second
	//}

	//LARGE_INTEGER frame_end_time{};

	////create loop
	//while (game_window.isOpen())
	//{
	//	newWindWidth = static_cast<float>(game_window.getSize().x);
	//	newWindHeight = static_cast<float>(game_window.getSize().y);

	//	//time_to_change_texture += delta_time;

	//	//game_timer += delta_time;

	//	//initial_pos_x = static_cast<float>(newWindWidth) / 2.f;
	//	//initial_pos_y = static_cast<float>(newWindHeight) - 20.f;

	//	//RESIZE sprites when game_window have resized
	//	/*
	//	This will update the render area to the dimensions of the game_window every
	//	time the game_window is resized rather than scaling the render area to fit the game_window.
	//	*/
	//	if (game_event.type == sf::Event::Resized)
	//	{
	//		newWindWidth = static_cast<float>(game_event.size.width);
	//		newWindHeight = static_cast<float>(game_event.size.height);
	//	//	//Update game_windows view
	//	//	//It's independent from resizing game_window
	//	//	sf::Vector2f origin(0, 0);
	//	//	sf::Vector2f new_size(newWindWidth, newWindHeight);
	//	//	sf::FloatRect resized_view(origin, new_size);
	//	//	game_window.setView(sf::View(resized_view));

	//	//	//Noew get the minimum of the resizing scales
	//	//	float scaleWidth = newWindWidth / static_cast<float>(initWindWidth);
	//	//	float scaleHeight = newWindHeight / static_cast<float>(initWindHeight);
	//	//	float scale = std::min(scaleWidth, scaleHeight);

	//	//	//Resize all sprites
	//	//	dwgs_access->paddle.sprite.setScale(individual_nscale(scale, paddle_scale));

	//	//	//Posistion didn't changed, but should
	//	//	dwgs_access->paddle.sprite.setPosition(individual_nscale(scale, dwgs_access->paddle.sprite.getPosition()));

	//	}


	//	//check the type of the event...
	//	while (game_window.pollEvent(game_event))
	//	{
	//		// game_window closed
	//		if (game_event.type == sf::Event::Closed)
	//		{
	//			game_window.close();
	//			break;
	//		}

	//	//	// key pressed
	//	//	else if (game_event.type == sf::Event::KeyPressed)
	//	//	{
	//	//		//CHANGE ABILITIES

	//	//		if (game_event.key.code == sf::Keyboard::A)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_50));
	//	//		else if (game_event.key.code == sf::Keyboard::S)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_1));
	//	//		else if (game_event.key.code == sf::Keyboard::D)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_2));
	//	//		else if (game_event.key.code == sf::Keyboard::F)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_3));
	//	//		else if (game_event.key.code == sf::Keyboard::G)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_4));
	//	//		else if (game_event.key.code == sf::Keyboard::H)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_5));
	//	//		else if (game_event.key.code == sf::Keyboard::J)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_100_6));
	//	//		else if (game_event.key.code == sf::Keyboard::K)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_250));
	//	//		else if (game_event.key.code == sf::Keyboard::L)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(PLUS_500));
	//	//		else if (game_event.key.code == sf::Keyboard::X)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(SLOW));
	//	//		else if (game_event.key.code == sf::Keyboard::C)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(FAST));
	//	//		else if (game_event.key.code == sf::Keyboard::V)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(THREE_BALLS));
	//	//		else if (game_event.key.code == sf::Keyboard::B)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(RED_FIRE));
	//	//		else if (game_event.key.code == sf::Keyboard::N)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(GREEN_FIRE));
	//	//		else if (game_event.key.code == sf::Keyboard::M)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(MAKE_TINY));
	//	//		else if (game_event.key.code == sf::Keyboard::Q)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(MAKE_WIDE));
	//	//		else if (game_event.key.code == sf::Keyboard::W)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(WITH_TOKEN));
	//	//		else if (game_event.key.code == sf::Keyboard::E)
	//	//			dwgs_access->abilities.at(0).sprite.setTexture(dwgs_access->abilities_texture.at(EMPTY));

	//	//		//CHANGE BALLS
	//	//		else if (game_event.key.code == sf::Keyboard::U)
	//	//			dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(SMALL), true);
	//	//		else if (game_event.key.code == sf::Keyboard::I)
	//	//			dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(MEDIUM), true);
	//	//		else if (game_event.key.code == sf::Keyboard::O)
	//	//			dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(LARGE), true);
	//	//		else if (game_event.key.code == sf::Keyboard::P)
	//	//			dwgs_access->ball.sprite.setTexture(dwgs_access->balls_texture.at(EXTRA_LARGE), true);

	//	//		//CHANGE PADDLES
	//	//		else if (game_event.key.code == sf::Keyboard::Num1) {
	//	//			dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CAPSULE_1), true);
	//	//			dwgs_access->paddle.sprite.setOrigin(capsule_origin);
	//	//		}
	//	//		else if (game_event.key.code == sf::Keyboard::Num2) {
	//	//			dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CAPSULE_2), true);
	//	//			dwgs_access->paddle.sprite.setOrigin(capsule_origin);
	//	//		}
	//	//		else if (game_event.key.code == sf::Keyboard::Num3) {
	//	//			dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CAPSULE_3), true);
	//	//			dwgs_access->paddle.sprite.setOrigin(capsule_origin);
	//	//		}
	//	//		else if (game_event.key.code == sf::Keyboard::Num4) {
	//	//			dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CONNECTOR_1), true);
	//	//			dwgs_access->paddle.sprite.setOrigin(connector_origin);
	//	//		}
	//	//		else if (game_event.key.code == sf::Keyboard::Num5) {
	//	//			dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CONNECTOR_2), true);
	//	//			dwgs_access->paddle.sprite.setOrigin(connector_origin);
	//	//		}
	//	//		else if (game_event.key.code == sf::Keyboard::Num6) {
	//	//			dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(CONNECTOR_3), true);
	//	//			dwgs_access->paddle.sprite.setOrigin(connector_origin);
	//	//		}
	//	//		else if (game_event.key.code == sf::Keyboard::Num7) {
	//	//			dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(WIDE), true);
	//	//			dwgs_access->paddle.sprite.setOrigin(wide_origin);
	//	//		}
	//	//		else if (game_event.key.code == sf::Keyboard::Num8) {
	//	//			dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(TINY), true);
	//	//			dwgs_access->paddle.sprite.setOrigin(tiny_origin);
	//	//		}

	//		//}


	//		// we don't process other types of events
	//		else
	//			break;
	//	}

	//	//========SIMULATE THE PHYSICS========

	//	//simulate_game();

	//	//_______________PADDLE_______________

	//	//acceleration_x = 0.f;

	//	////Recalculation parameters from keyboard
	//	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//	//   //move left
	//	//{
	//	//	//acceleration_x -= 600.f;
	//	//	speed_x -= 100.f;
	//	//}
	//	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//	////move right
	//	//{
	//	//	//acceleration_x += 600.f;
	//	//	speed_x += 100.f;
	//	//}

	//	////#3 Change of accelerations because of frictions
	//	////Re-calculate OBJECT acceleration according to new acceleration, new speed and friction
	//	//acceleration_x -= speed_x * 7.5f;

	//	////#4
	//	////Re-calculate OBJECT position of the rocket
	//	//d_x = speed_x * delta_time + acceleration_x * delta_time * delta_time / 2.f;

	//	////#5
	//	/////!! Re-calculate OBJECT speed for the next cycle - only now you can do this
	//	//speed_x += acceleration_x * delta_time;

	//	//sf::Vector2f offset(d_x, 0);
	//	//dwgs_access->paddle.sprite.move(offset);

	//	//sf::FloatRect paddle_box = dwgs_access->paddle.sprite.getGlobalBounds();

	//	////Left box
	//	//sf::Vector2f l_pos(-200.f, 0);
	//	//sf::Vector2f l_size(200.f, newWindHeight);
	//	//sf::FloatRect left_menu(l_pos, l_size);

	//	////Right box
	//	//sf::Vector2f r_pos(newWindWidth, 0);
	//	//sf::Vector2f r_size(200.f, newWindHeight);
	//	//sf::FloatRect right_menu(r_pos, r_size);

	//	//sf::Vector2f bounce_x{};
	//	//std::cout << "newWindWidth = " << newWindWidth << '\n';
	//	//std::cout << "Left = " << paddle_box.left << ", Right = " << (paddle_box.left + paddle_box.width) << '\n';
	//	//if (paddle_box.left < 0)
	//	//{
	//	//	bounce_x = { paddle_box.width / 2.f, initial_pos_y };
	//	//	std::cout << "left bellow '0'... bounce_x = " << bounce_x.x << '\n';
	//	//	std::cout << "time = " << game_timer << '\n';
	//	//	dwgs_access->paddle.sprite.setPosition(bounce_x);

	//	//	speed_x *= (-1.f) * 0.75f;
	//	//}
	//	//else if ((paddle_box.left + paddle_box.width) > newWindWidth)
	//	//{

	//	//	bounce_x = { newWindWidth - paddle_box.width / 2.f, initial_pos_y };
	//	//	std::cout << "right overflow... bounce_x = " << bounce_x.x << '\n';
	//	//	std::cout << "time = " << game_timer << '\n';
	//	//	dwgs_access->paddle.sprite.setPosition(bounce_x);

	//	//	speed_x *= (-1.f) * 0.75f;
	//	//}

	//	//


	//	//==========RENDER THE GAME===========

	//	//render_game();

	//	//Clear screen
	//	game_window.clear(sf::Color::Black);

	//	//_________MAIN FIELD TEXTURE_________

	//	game_window.draw(game_frame);

	//	//_________LEGEND FIELD TEXTURE_________

	//	game_window.draw(legend_frame);

	//	//_________SCORE FIELD TEXTURE_________

	//	game_window.draw(status_frame);

	//	// Draw LOGO
	//	//game_window.draw(logo_text);

	//	// Draw SCORE label
	//	//game_window.draw(score_text);


	//	//___________PADDLE TEXTURE___________
	//	//if (time_to_change_texture > change_paddle_wait)
	//	//{
	//	//	if (p_number == CAPSULE_3) p_number = CAPSULE_1;
	//	//	dwgs_access->paddle.sprite.setTexture(dwgs_access->paddles_texture.at(p_number++), true);
	//	//	time_to_change_texture = 0;
	//	//}


	//	//Draw BLOCKS
	//	//for (auto& block : dwgs_access->blocks)
	//	//{
	//	//	dwgs_access->resize_sprite(block, blocks_scale);
	//	//	dwgs_access->draw_object(game_window, block);
	//	//}

	//	////Draw ABILITIES
	//	//dwgs_access->draw_object(game_window, dwgs_access->abilities.at(0));

	//	////Draw BALL
	//	//dwgs_access->draw_object(game_window, dwgs_access->ball);

	//	////Draw PADDLE
	//	//dwgs_access->draw_object(game_window, dwgs_access->paddle);

	//	//Display everything to the screen
	//	game_window.display();




	//	//=====TIME RECALCULATION=====

	//	QueryPerformanceCounter(&frame_end_time);  // here we finish to calculate time in the CPU units

	//	//static_cast<float>(frame_end_time.QuadPart - frame_begin_time.QuadPart) - this gives you how many cycles were spent on the current frame
	//	delta_time = static_cast<float>(frame_end_time.QuadPart - frame_begin_time.QuadPart) / perfomance_frequancy; // time in seconds
	//	frame_begin_time = frame_end_time; // here we start to measure delta_time of the new frame
	//}
	
	return 0;
}