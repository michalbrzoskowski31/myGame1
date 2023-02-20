#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"

class Game
{
public:
	Game();
	virtual ~Game();

	// Inits
		void initWindow();

	// Accessors
		bool isRunning() const;

	// Public functions
		void update();
		void render();

private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event sfmlEvent;

	Player player{};


	void pollEvents();

	bool endGame;
};

