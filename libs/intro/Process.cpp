#include "Process.hpp"

Intro::Process::Process(sf::RenderWindow* parent_window)
{	 //?
	_parent = parent_window;
}

Intro::Process::~Process()
{
	//?
	_parent = nullptr;
}

bool Intro::Process::isRunning() const { return _running; }

void Intro::Process::tickTimer(float tick) { _blinkTimer += tick; }

void Intro::Process::blinkInstruction(Intro::Statics& utils)
{
	if (_blinkTimer > _blinkAwait)
	{
		if (utils.getInstructionColor() == sf::Color::Yellow)
		{
			utils.setInstructionColor(sf::Color::Black);
		}
		else
		{
			utils.setInstructionColor(sf::Color::Yellow);
		}

		_blinkTimer = 0;
	}
}

void Intro::Process::render(const Intro::Statics& utils)
{
	// Before do anything: clear screen
	_parent->clear(sf::Color::Black);

	// Draw LOGO
	_parent->draw(utils.getLogo());
	// Draw INSTRUCTION
	_parent->draw(utils.getInstruction());

	// Now send drawings to the screen
	_parent->display();
}

void Intro::Process::interact(sf::RenderWindow& window)
{
	while (window.pollEvent(_event))
	{
		// application_window closed
		if (_event.type == sf::Event::Closed)
		{
			_running = false;	 // also should be here
			window.close();
			break;
		}
		else if (_event.type == sf::Event::KeyPressed)
		{
			// Also close by 'Esc' keyboard button
			if (_event.key.code == sf::Keyboard::Escape)
			{
				_running = false;	 // also should be here
				window.close();
				break;
			}
			// Press enter and winish Intro page
			else if (_event.key.code == sf::Keyboard::Enter)
			{
				_running = false;
				break;
			}
		}
	}
}
