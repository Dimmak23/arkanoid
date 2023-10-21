//* WIN API
#include <Windows.h>

//* SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//* C++ STD
#include <iostream>

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
int main()
{
	// Create a window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

	// Create a circle shape
	sf::CircleShape circle(50);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(375, 275);

	// // Load and play a sound
	// sf::SoundBuffer buffer;
	// if (!buffer.loadFromFile("path_to_your_sound.wav"))
	// {
	// 	// Handle the case where the sound file couldn't be loaded
	// 	return -1;
	// }
	// sf::Sound sound(buffer);
	// sound.play();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(circle);
		window.display();
	}

	return 0;
}
