#include "game.h"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	
	Game game;

	if (!game.init())
		return EXIT_FAILURE;

	game.run();

	return EXIT_SUCCESS;
}
