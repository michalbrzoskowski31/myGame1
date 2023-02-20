#include "Game.h"

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    Game game;

    // Game loop
    while (game.isRunning())
    {
        game.update();
        game.render();
    }

	return 0;
}

