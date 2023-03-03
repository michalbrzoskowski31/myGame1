#pragma once

#include <vector>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Block.h"
#include "Platform.h"
#include "Ball.h"
#include "Enemy.h"
//#include "Textures.h"

class Game
{
public:
	Game();
	virtual ~Game();

	// Inits
		void initWindow();
		void loadTextures();
		void initStructures();

	// Accessors
		bool isRunning() const;

	// Public functions
		void update();
		void render();

		//void updateCollision();


		//Platform* platform1_ptr;
		std::vector<Platform> platforms;
		std::vector<Ball> balls;
		std::vector<Enemy> enemies;

private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event sfmlEvent;

	sf::Texture blockDefaultTexture;
	sf::Texture blockGrassTexture;

	sf::Texture backgroundTexture; // nie podoba mi si� to t�o tutaj

	sf::Texture playerTexture;
	sf::Texture ballTexture;
	sf::Texture gunTexture;

	sf::Texture enemy1Texture, enemy2Texture, enemy3Texture, enemy4Texture, enemy5Texture;
	sf::Texture* enemiesTextures[5] = {&enemy1Texture, &enemy2Texture, &enemy3Texture, &enemy4Texture, &enemy5Texture};

	sf::Sprite background_sprite;

	Player* player;
	//Block block1{ 500.f, 700.f};
	//Platform platform1{ 100, 500, 5, 1, &blockGrass};



	void pollEvents();

	bool endGame;
};

