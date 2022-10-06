#pragma once

#include <SFML/System/Vector2.hpp>

sf::Vector2f individual_nscale(const float& nscale, sf::Vector2f indi_sprite)
{
	indi_sprite *= nscale;
	return indi_sprite;
}