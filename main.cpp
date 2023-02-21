#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


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

