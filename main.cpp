#include <fstream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


#include "Game.h"


int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    std::fstream dataFileW;
    std::istringstream dataFileR;
    //dataFile.open("data.txt");



    Game game;
    

    std::string bestScore;
    dataFileW.open("dataFile.txt");
    std::getline(dataFileW, bestScore);
    dataFileR.str(bestScore);
    int bestScoreFinal;
    dataFileR >> bestScoreFinal;
    game.setBestScore(bestScoreFinal);
    dataFileW.close();
    // Game loop
    while (game.isRunning())
    {
        game.update();
        game.render();
    }

    dataFileW.open("dataFile.txt");
    dataFileW << game.getKills();
    dataFileW.close();

	return 0;
}

