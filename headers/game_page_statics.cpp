#include "game_page_statics.hpp"

//Colossal class constructor moved here

Game::staticUnits::staticUnits(const Util::staticUnits& utils)
{
	//std::cout << "Games::staticUnits construction\n";

//==================================GRID===============================

	//==LEGEND_FIELD_INIT==

	initialize_frame(
		legend_frame,
		to_f(legend_field.overall_width),
		to_f(legend_field.overall_height),
		sf::Color::Red,
		sf::Color::Black,
		to_f(outline.outside_thk),
		to_f(legend_field.origin_x),
		to_f(legend_field.origin_y)
	);

	//===MAIN_FIELD_INIT===

	initialize_frame(
		game_frame,
		to_f(game_field.overall_width),
		to_f(game_field.overall_height),
		sf::Color::Red,
		sf::Color::Black,
		to_f(outline.outside_thk),
		to_f(game_field.origin_x),
		to_f(game_field.origin_y)
	);

	//==SCORE_FIELD_INIT==

	initialize_frame(
		status_frame,
		to_f(status_field.overall_width),
		to_f(status_field.overall_height),
		sf::Color::Red,
		sf::Color::Black,
		to_f(outline.outside_thk),
		to_f(status_field.origin_x),
		to_f(status_field.origin_y)
	);

	//==CONVEYOR_EXTENSIONS==

	extension_lines.resize(Default::conveyor_mapping.size());

	int index{};
	for (auto& line : extension_lines)
	{
		line.setSize(sf::Vector2f(to_f(game_field.overall_width), to_f(outline.outside_thk)));
		line.setFillColor(sf::Color::Red);
		line.setPosition(
			sf::Vector2f(
									to_f(game_field.origin_x), 
									to_f(game_field.origin_y + Default::conveyor_mapping.at(index++))
								)
		);
	}

//=============================LEGEND FRAME============================	

	//=====BLOCKS LABEL SETTINGS=====

	Util::initialize_text(
		blocks_label,
		"Blocks legend:",
		utils.main_font,
		12,
		false,
		to_f(legend_field.origin_x + 20),
		to_f(legend_field.origin_y + 20),
		sf::Text::Underlined | sf::Text::Bold,
		sf::Color::Red
	);

	//=====BLOCKS DESCRIPTIONS SETTINGS=====

	blocks_descriptions.resize(BLK_T_COUNT / 2);		//20: different blocks, but only 10 unique color

	index = 0;
	std::string block_value_label;
	for (auto& description : blocks_descriptions)
	{
		block_value_label = "+";
		block_value_label += std::to_string(Util::block_values.at(index));
		block_value_label += " points";

		Util::initialize_text(
			description,
			block_value_label,
			utils.main_font,
			9,
			false,
			to_f(legend_field.origin_x + 20),
			to_f(
			legend_field.origin_y
			+ blocks_label.getGlobalBounds().top
			+ blocks_label.getGlobalBounds().height
			+ 50 * (index + 1)
		),
			sf::Text::Regular,
			sf::Color::Red
		);
		index++;
	}

	//=====ABILITIES LABEL SETTINGS=====

	Util::initialize_text(
		abilities_label,
		"Abilities legend:",
		utils.main_font,
		12,
		false,
		to_f(legend_field.origin_x + 20),
		to_f(
		legend_field.origin_y
		+ blocks_descriptions.at(BLK_T_COUNT / 2 - 1).getGlobalBounds().top
		+ blocks_descriptions.at(BLK_T_COUNT / 2 - 1).getGlobalBounds().height
		+ 30
	),
		sf::Text::Underlined | sf::Text::Bold,
		sf::Color::Red
	);

	//=====ABILITIES DESCRIPTIONS SETTINGS=====

	abilities_descriptions.resize(10);		//10: different abilities

	index = 0;
	for (auto& description : abilities_descriptions)
	{
		Util::initialize_text(
			description,
			ab_names.at(index),
			utils.main_font,
			9,
			false,
			to_f(legend_field.origin_x + 20),
			to_f(
			legend_field.origin_y
			+ abilities_label.getGlobalBounds().top
			+ abilities_label.getGlobalBounds().height
			+ 50 * (index + 1)
		),
			sf::Text::Regular,
			sf::Color::Red
		);
		index++;
	}

//=============================STATUS FRAME============================	


	//=====STATUS LABELS SETTINGS=====

	status_labels.resize(st_names.size());		//6: different statuses

	index = 0;
	for (auto& label : status_labels)
	{
		Util::initialize_text(
			label,
			st_names.at(index),
			utils.main_font,
			12,
			false,
			to_f(status_field.origin_x + 20),
			to_f(status_field.origin_y + pos_y_st_labels.at(index)),
			sf::Text::Underlined | sf::Text::Bold,
			sf::Color::Red
		);
		index++;
	}

	//=====TIMERS ADDITIONALS=====

	//Game time:
	
	//Util::initialize_text(
	//	timer_adder,
	//	sec,
	//	utils.main_font,
	//	10,
	//	false,
	//	status_labels.at(TIMER_LABEL).getGlobalBounds().left + 60.f,
	//	status_labels.at(TIMER_LABEL).getGlobalBounds().top
	//			+ status_labels.at(TIMER_LABEL).getGlobalBounds().height
	//			+ 20.f,
	//	sf::Text::Regular,
	//	sf::Color::Red
	//);

	//Countdown timer:

	//Util::initialize_text(
	//	countdown_adder,
	//	sec,
	//	utils.main_font,
	//	10,
	//	false,
	//	status_labels.at(REV_COUNT_LABEL).getGlobalBounds().left + 50.f,
	//	status_labels.at(REV_COUNT_LABEL).getGlobalBounds().top
	//			+ status_labels.at(REV_COUNT_LABEL).getGlobalBounds().height
	//			+ 20.f,
	//	sf::Text::Regular,
	//	sf::Color::Red
	//);

	//=====LIFES CIRCLES OUTLINE SETTINGS=====

	lifes_outline.resize(MAX_LIFES);

	index = 0;
	float vert_adder{};
	float hor_adder{};
	for (auto& circle : lifes_outline)
	{
		circle.setRadius(10.f);
		circle.setFillColor(sf::Color::Black);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(1.f);
		circle.setOrigin(sf::Vector2f(circle.getLocalBounds().width / 2, circle.getLocalBounds().height / 2));
		circle.setPosition(
					sf::Vector2f(
											status_labels.at(LIFES_LABEL).getGlobalBounds().left + 10.f + hor_adder,
											status_labels.at(LIFES_LABEL).getGlobalBounds().top
											+ status_labels.at(LIFES_LABEL).getGlobalBounds().height
											+ 40.f
											+ vert_adder
										)
		);

		index++;
		if (!(index % 9))
		{
			vert_adder += 30.f;
			hor_adder = 0;
		}
		else hor_adder += 30.f;
	}

	//=====BALL PARAMETERS SETTINGS=====

	ball_parameters.resize(parameters_names.size());

	index = 0;
	hor_adder = 0;
	float ver_adder{};
	for (auto& parameter : ball_parameters)
	{
		Util::initialize_text(
			parameter,
			parameters_names.at(index),
			utils.main_font,
			9,
			false,
			to_f(status_field.origin_x + 20 + hor_adder),
			to_f(status_field.origin_y
						+ status_labels.at(BALL_LABEL).getGlobalBounds().top
						+ status_labels.at(BALL_LABEL).getGlobalBounds().height
						+ 20
						+ ver_adder
						),
			sf::Text::Regular,
			sf::Color::Red
		);

		index++;

		if (index < 3) ver_adder = 30.f * index;
		else ver_adder = 30.f * (index - 3);

		if ( !(index % 3) )
			hor_adder = to_f(status_field.overall_width / 2 - 10.f);

	}

	//=====BALL FRAMES SETTINGS=====

	ball_p_frames.resize(ball_parameters.size());
	index = 0;
	for (auto& frame : ball_p_frames)
	{
		initialize_frame(
			frame,
			90.f,
			25.f,
			sf::Color::Red,
			sf::Color::Black,
			0.75f,
			to_f(ball_parameters.at(index).getGlobalBounds().left + 30.f),
			to_f(ball_parameters.at(index).getGlobalBounds().top - 10.f)
		);
		index++;
	}

	//=====PADDLE PARAMETERS SETTINGS=====

	paddle_parameters.resize(parameters_names.size() / 2);

	index = 0;
	for (auto& parameter : paddle_parameters)
	{
		Util::initialize_text(
			parameter,
			parameters_names.at(index),
			utils.main_font,
			9,
			false,
			to_f(status_field.origin_x + 20),
			to_f(status_field.origin_y
						+ status_labels.at(PADDLE_LABEL).getGlobalBounds().top
						+ status_labels.at(PADDLE_LABEL).getGlobalBounds().height
						+ 20
						+ 30 * index
					),
			sf::Text::Regular,
			sf::Color::Red
		);
		index++;
	}

	//=====PADDLE FRAMES SETTINGS=====

	paddle_p_frames.resize(paddle_parameters.size());
	index = 0;
	for (auto& frame : paddle_p_frames)
	{
		initialize_frame(
			frame,
			90.f,
			25.f,
			sf::Color::Red,
			sf::Color::Black,
			0.75f,
			to_f(paddle_parameters.at(index).getGlobalBounds().left + 30.f),
			to_f(paddle_parameters.at(index).getGlobalBounds().top - 10.f)
		);
		index++;
	}

//===============================TEXTURES==============================	

	/*
	
	NOTE:

	These textures will be used in the Game::dynamicUnits

	*/

	//BLOCKS

	int texture_address{ 1 };
	blk_textures.resize(BLK_T_COUNT);
	for (auto& texture : blk_textures)
	{
		Util::safe_parse(
			texture,
			(textures_path + ((texture_address < 10) ? "0" : "") + std::to_string(texture_address) + adder_path),
			(textures_path + std::to_string(texture_address) + adder_path + template_message).c_str()
		);
		texture_address++;
	}

	//ABILITIES

	texture_address = 31;
	abl_textures.resize(ABILITY_COUNT);
	for (auto& texture : abl_textures)
	{
		while (std::ranges::find(skipped_abl_textures_addresses, texture_address) != skipped_abl_textures_addresses.end())
		{
			texture_address++;
		}
		Util::safe_parse(
			texture,
			(textures_path + std::to_string(texture_address) + adder_path),
			(textures_path + std::to_string(texture_address) + adder_path + template_message).c_str()
		);
		texture_address++;
	}

	//PADDLES

	texture_address = 82;
	pdl_textures.resize(PADDLE_COUNT);
	for (auto& texture : pdl_textures)
	{
		while (std::ranges::find(skipped_pdl_textures_addresses, texture_address) != skipped_pdl_textures_addresses.end())
		{
			texture_address++;
		}
		Util::safe_parse(
			texture,
			(textures_path + std::to_string(texture_address) + adder_path),
			(textures_path + std::to_string(texture_address) + adder_path + template_message).c_str()
		);
		texture_address++;
	}

	//BALL

	texture_address = 63;
	Util::safe_parse(
		bll_texture,
		(textures_path + std::to_string(texture_address) + adder_path),
		(textures_path + std::to_string(texture_address) + adder_path + template_message).c_str()
	);

//================================SPRITES==============================	

	index = 0;
	int src_index{};
	blk_sprites.resize(blocks_descriptions.size());
	for (auto& sprite : blk_sprites)
	{
		sprite.setTexture(blk_textures.at(index), true);
		sprite.setScale(sf::Vector2f(0.2f, 0.2f));
		sprite.setPosition(
			sf::Vector2f(
			blocks_label.getGlobalBounds().left,
			blocks_descriptions.at(src_index).getGlobalBounds().top - 30.f
		)
		);
		index += 2;
		src_index++;

	}

	index = 0;
	src_index = 0;
	abl_sprites.resize(abilities_descriptions.size());
	for (auto& sprite : abl_sprites)
	{
		sprite.setTexture(abl_textures.at(index), true);
		sprite.setScale(sf::Vector2f(0.16f, 0.2f));
		sprite.setPosition(
			sf::Vector2f(
			abilities_label.getGlobalBounds().left,
			abilities_descriptions.at(src_index).getGlobalBounds().top - 30.f
		)
		);
		index++;
		src_index++;
	}

}
