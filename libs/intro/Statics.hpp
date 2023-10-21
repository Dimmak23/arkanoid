#pragma once

//* C++ STD
#include <iostream>
#include <memory>

//* SFML
#include <SFML/Graphics/Text.hpp>

//* Custom headers
#include "Utilities.hpp"

namespace Intro
{
	class Statics
	{
	public:
		Statics() = default;
		Statics(const Utilities::StaticUnits* utils);

		// # API

		//? Need to know color to change it
		sf::Color getInstructionColor() const;
		//? Actually change it
		void setInstructionColor(const sf::Color& new_color);

		//?
		const sf::Text& getLogo() const;
		const sf::Text& getInstruction() const;

	private:
		//? Let's prevent copying Game object
		Statics(const Statics&) = delete;
		Statics& operator=(const Statics&) = delete;

		//^ Members
		//! REMEMBER: Fonts, Texts, Textures, ContextSettings,...(what else?) - can't be global. They should be
		//! someone's property
		sf::Text _logo;
		sf::Text _instruction;
	};
};	  // namespace Intro
