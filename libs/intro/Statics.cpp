#include "Statics.hpp"

Intro::Statics::Statics(const Utilities::StaticUnits* utils)
{
	//=====LOGO SETTINGS=====

	Utilities::initialize_text(
		_logo, "(ARKANOID)", utils->logo_font, 80, true,
		to_f(outline.overall_width / 2),	 // Position depend on the one that we have set up in the outline
		to_f(outline.overall_height / 2),	 // Position depend on the one that we have set up in the outline
		sf::Text::Bold, sf::Color::Blue);

	//=====INSTRUCTION TO START SETTINGS=====

	Utilities::initialize_text(
		_instruction, "Please, press the ENTER key to start the game...", utils->main_font, 14, true,
		to_f(outline.overall_width / 2),		   // Position depend on the one that we have set up in the outline
		to_f(outline.overall_height / 2 + 140),	   // Position depend on the one that we have set up in the outline
		sf::Text::Bold, sf::Color::Yellow);
}

sf::Color Intro::Statics::getInstructionColor() const { return _instruction.getFillColor(); }

void Intro::Statics::setInstructionColor(const sf::Color& new_color) { _instruction.setFillColor(new_color); }

const sf::Text& Intro::Statics::getLogo() const { return _logo; }

const sf::Text& Intro::Statics::getInstruction() const { return _instruction; }
