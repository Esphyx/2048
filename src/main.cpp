#include <iostream>
#include "game.hpp"

int main()
{
	Game *game = new Game(false);

	while (!game->isGameOver())
		game->move(game->read());

	return 0;
}