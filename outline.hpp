#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//							THIS IS THE STORAGE FOR OVERALL SIZES						    //
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//Outline have been built on the block width
constexpr int block_width{ 96 };
//and they quantity in the line
constexpr int maxInLine{ 12 };

struct sizes
{
	const unsigned int overall_width{};
	const unsigned int overall_height{};
	const unsigned int outside_thk{};
	const unsigned int frame_thk{};
};

//These properties are dependencies for other fileds
static sizes outline{1800, 1200, 3, 2};

static sizes game_field{
	block_width * maxInLine,	//space for all available blocks

	outline.overall_height - 2 * (outline.frame_thk+outline.outside_thk), //the whole available space

	outline.outside_thk,
	outline.frame_thk
};

//STATUS and LEGEND fields will be symmetrical
static sizes status_field{
	
	(outline.overall_width - game_field.overall_width) / 2  //half of the available space after game field
	- (outline.frame_thk + outline.outside_thk) //space to the game border
	- (2 * outline.frame_thk + outline.outside_thk), //space between game field and status/legend fields
	
	game_field.overall_height, //the same height as game field
	
	outline.outside_thk,
	outline.frame_thk
};

static sizes legend_field{

	status_field.overall_width, //the same width as status field

	game_field.overall_height, //the same height as game field

	outline.outside_thk,
	outline.frame_thk
};
