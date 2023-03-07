#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cmath>

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
#include "Animation.h"
//#include "Textures.h"

#define GRID 50

class Game
{
public:
	Game();
	virtual ~Game();

	// Inits
		void initWindow();
		void loadTextures();
		void initStructures();
		void loadFonts();
		void initVariables();
		void initPlayer();
		void initText();

	// Accessors
		bool isRunning() const;
		int getKills() const;
		int getBestScore() const;
		
		void setBestScore(int score);

	// Public functions
		void update();
		void render();

		//void updateCollision();


		//Platform* platform1_ptr;
		std::vector<Platform> platforms;
		std::vector<Ball> balls;
		std::vector<Enemy> enemies;
		std::vector<sf::Sprite> fire;
		std::vector<sf::Sprite> HPBar;

		float deltaTime;
		sf::Clock clock;

		float enemySpawnChance[5];

private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event sfmlEvent;
	sf::Font font1;
	sf::Font font2;

	sf::Text gameInfo;
	sf::Text GAMEOVER;
	//sf::Text summary;
	sf::Text scoreTxt;
	sf::Text bestScoreTxt;
	sf::Text accuracyTxt;
	sf::Text FPSTxt;


	sf::Texture blockDefaultTexture;
	sf::Texture blockGrassTexture;

	sf::Texture backgroundTexture;
	//sf::Sprite fire;
	sf::Texture fireTexture;
	Animation* fireAnimation;
	//Animation fireAnimation;

	sf::Texture playerTexture;
	sf::Texture ballTexture;
	sf::Texture gunTexture;
	sf::Texture heartTexture;

	sf::Texture enemy1Texture, enemy2Texture, enemy3Texture, enemy4Texture, enemy5Texture;
	sf::Texture* enemiesTextures[5] = {&enemy1Texture, &enemy2Texture, &enemy3Texture, &enemy4Texture, &enemy5Texture};

	sf::Sprite background_sprite;

	Player* player;
	

	int hitShots;
	int bestScore;

	void pollEvents();

	bool endGame;
};

