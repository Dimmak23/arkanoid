#include "GameApplication.hpp"

int main(int argc, char** argv)
{
	std::unique_ptr<Arkanoid::GameApplication> arkanoid = std::make_unique<Arkanoid::GameApplication>(argc, argv);

	arkanoid->run();

	return 0;
}
