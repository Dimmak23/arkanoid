#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//							THIS IS THE STORAGE FOR OVERALL SIZES						    //
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

namespace Default
{
	//Outline have been built on the block width
	constexpr int block_width{ 96 };
	//and height
	constexpr int block_height{ 32 };
	//and they quantity in the line
	constexpr int maxInLine{ 12 };
	//and they quantity in the column
	constexpr int maxRows{ 12 };
}

struct sizes
{
	const unsigned int overall_width{};
	const unsigned int overall_height{};
	const unsigned int origin_x{};
	const unsigned int origin_y{};
	const unsigned int outside_thk{};
	const unsigned int empty_thk{};
};

//These properties are dependencies for other fileds
static const sizes outline{1800, 1200, 0, 0, 1, 4};

static const sizes game_field{
	Default::block_width * Default::maxInLine,	//space for all available blocks

	outline.overall_height - 2 * (outline.empty_thk + outline.outside_thk), //the whole available space

	outline.origin_x
	+ (outline.overall_width - Default::block_width * Default::maxInLine) / 2,  //half of the available space after game field

	outline.origin_y
	+ outline.empty_thk + outline.outside_thk,

	outline.outside_thk,
	outline.empty_thk
};

//STATUS and LEGEND fields will be symmetrical

static const sizes legend_field{

	(outline.overall_width - game_field.overall_width) / 2		//half of the available space after game field
	- (outline.empty_thk + outline.outside_thk)					//space to the game border
	- (2 * outline.empty_thk + outline.outside_thk),			//space between game field and status/legend fields

	game_field.overall_height, //the same height as game field

	outline.origin_x + outline.empty_thk + outline.outside_thk,

	game_field.origin_y, //the origin_y as game field

	outline.outside_thk,
	outline.empty_thk
};

static const sizes status_field{

	legend_field.overall_width, //the same width as status field

	game_field.overall_height, //the same height as game field

	outline.overall_width
	- outline.empty_thk - outline.outside_thk
	- legend_field.overall_width,

	game_field.origin_y, //the origin_y as game field

	outline.outside_thk,
	outline.empty_thk
};
