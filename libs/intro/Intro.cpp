#include "Intro.hpp"

Intro::Page::Page(sf::RenderWindow* parent_window, Utilities::StaticUnits* utility_statics)
{	 //?
	_parent = parent_window;

	//?
	_utility = utility_statics;

	//?
	_statics = std::make_unique<Intro::Statics>(_utility);
	_process = std::make_unique<Intro::Process>(_parent);

	std::cout << "Intro::Page with size: " << sizeof(*this) << " bytes successefully constructed...\n";
}

Intro::Page::~Page()
{
	std::cout << "Intro::Page destroyed...\n";

	//?
	_parent = nullptr;

	//? Release Intro's that we don't need anymore
	// _statics.reset(nullptr);
	// _process.reset(nullptr);

	//?
	_utility = nullptr;
}

bool Intro::Page::run()
{
	//? Start timer update
	Utilities::Process::resetStartPoint();

	//? Hold Intro page until user will respond
	while (_process->isRunning())
	{
		//? Check timer and blink instruction
		_process->blinkInstruction(*_statics);

		//? Render screen the Intro objects
		_process->render(*_statics);

		//? Check user inputs
		_process->interact(*_parent);

		//? Process feature should know what time is it
		Utilities::Process::updateDelta();
		_process->tickTimer(Utilities::Process::delta_time);
	}

	return true;
}
