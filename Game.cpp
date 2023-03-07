#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->loadTextures();
	this->loadFonts();
	this->initText();
	this->initStructures();
	this->initVariables();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->fireAnimation;
}

// Inits

void Game::initWindow()
{
	//sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height  <-- wymiary okna
	this->videoMode = sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
	this->window = new sf::RenderWindow{ this->videoMode, "myGame1", sf::Style::Fullscreen };
	this->window->setFramerateLimit(120);
}

void Game::loadTextures()
{
	this->fireTexture.loadFromFile("Textures/fireTexture.png");
	this->blockDefaultTexture.loadFromFile("Textures/block_ground.png");
	this->blockGrassTexture.loadFromFile("Textures/block_grass.png");
	this->backgroundTexture.loadFromFile("Textures/background.png");
	this->playerTexture.loadFromFile("Textures/player.png");
	this->ballTexture.loadFromFile("Textures/ball.png");
	this->gunTexture.loadFromFile("Textures/gun.png");

	this->enemy1Texture.loadFromFile("Textures/enemyLevel1.png");
	this->enemy2Texture.loadFromFile("Textures/enemyLevel2.png");
	this->enemy3Texture.loadFromFile("Textures/enemyLevel3.png");
	this->enemy4Texture.loadFromFile("Textures/enemyLevel4.png");
	this->enemy5Texture.loadFromFile("Textures/enemyLevel5.png");

	this->heartTexture.loadFromFile("Textures/heart.png");

	this->background_sprite.setTexture(backgroundTexture);
}

void Game::initStructures()
{
	//unsigned int grid = 50;
	float wWidth = static_cast<float>(sf::VideoMode::getDesktopMode().width);
	float wHeight = static_cast<float>(sf::VideoMode::getDesktopMode().height);

	this->fireAnimation = new Animation{ &fireTexture, sf::Vector2u(3, 1), 5.f };
	
	for (int i = 0; i < wWidth / 150.f; i ++)
	{
		this->fire.push_back(sf::Sprite{});
		this->fire.at(i).setTexture(fireTexture);
		this->fire.at(i).setScale(3.f, 3.f);
		this->fire.at(i).setPosition(i * 150.f, wHeight - 150.f);
	}

	for (int i = 0; i < 5; i++)
	{
		this->HPBar.push_back(sf::Sprite{});
		this->HPBar.at(i).setTexture(heartTexture);
		this->HPBar.at(i).setPosition((wWidth - 5 * heartTexture.getSize().x) / 2 + i * (heartTexture.getSize().x), 0.f); // Dodaæ jakiœ offset
	}

	this->platforms.push_back(Platform{ 150.f, wHeight / 1.5f, 10, 1, &blockGrassTexture });
	this->platforms.push_back(Platform{ wWidth - 150.f - 10 * GRID, wHeight / 1.5f, 10, 1, &blockGrassTexture });
	
	this->platforms.push_back(Platform{ wWidth / 2.f - 3 * GRID, wHeight / 1.2f, 6, 1, &blockDefaultTexture });

}

void Game::loadFonts()
{
	this->font1.loadFromFile("Fonts/orange juice 2.0.ttf");
	this->font2.loadFromFile("Fonts/coolvetica rg.otf");
}

void Game::initVariables()
{
	this->deltaTime = 0.f;
	this->enemySpawnChance[0] = 39.f;
	this->enemySpawnChance[1] = 30.f;
	this->enemySpawnChance[2] = 20.f;
	this->enemySpawnChance[3] = 10.f;
	this->enemySpawnChance[4] = 1.f;


	this->hitShots = 0;
	this->bestScore = 0;
}

void Game::initPlayer()
{
	this->player = new Player{ static_cast<float>(sf::VideoMode::getDesktopMode().width / 2.f), 500.f, true, 0.1, 10.0, 0.1, 0.1, 0.0, 0.0, &playerTexture, &gunTexture }; //static_cast<float>(sf::VideoMode::getDesktopMode().height / 2 - 500)

}

void Game::initText()
{
	// Game info
	this->gameInfo.setFont(font2);
	this->gameInfo.setCharacterSize(70);
	this->gameInfo.setFillColor(sf::Color::Black);
	this->gameInfo.setPosition(30.f, 30.f);

	// GAMEOVER
	this->GAMEOVER.setFont(font1);
	this->GAMEOVER.setCharacterSize(250);
	this->GAMEOVER.setFillColor(sf::Color::Red);
	this->GAMEOVER.setString("GAME OVER");
	this->GAMEOVER.setPosition((window->getSize().x - GAMEOVER.getGlobalBounds().width) / 2.f, window->getSize().y / 2.f - GAMEOVER.getGlobalBounds().height);

	float offset = 300;
	this->scoreTxt.setFont(font2);
	this->scoreTxt.setCharacterSize(50);
	this->scoreTxt.setFillColor(sf::Color::Red);
	this->scoreTxt.setPosition((window->getSize().x - offset) / 2.f, window->getSize().y / 2.f  + 100);

	this->bestScoreTxt.setFont(font2);
	this->bestScoreTxt.setCharacterSize(50);
	this->bestScoreTxt.setFillColor(sf::Color::Red);
	this->bestScoreTxt.setPosition((window->getSize().x - offset) / 2.f, window->getSize().y / 2.f + 150);

	this->accuracyTxt.setFont(font2);
	this->accuracyTxt.setCharacterSize(50);
	this->accuracyTxt.setFillColor(sf::Color::Red);
	this->accuracyTxt.setPosition((window->getSize().x - offset) / 2.f, window->getSize().y / 2.f + 200);

	this->FPSTxt.setFont(font2);
	this->FPSTxt.setCharacterSize(30);
	this->FPSTxt.setFillColor(sf::Color::Black);
	this->FPSTxt.setPosition(sf::VideoMode::getDesktopMode().width - 125.f, 5.f); //FPSTxt.getGlobalBounds().width

}

bool Game::isRunning() const
{
	return this->window->isOpen();
}

int Game::getKills() const
{
	return player->kills;
}

void Game::update()
{
	deltaTime = clock.restart().asSeconds();
	int FPS = static_cast<int>(pow(deltaTime, -1));


	static double playerSpawnDelay = 0.0;
	if (playerSpawnDelay > 120)
	{
		player->setIsRigid(false);
	}
	playerSpawnDelay += deltaTime * DT_MULTIPLIER;

	static double FPSDisplayDelay = 0.0;
	if (FPSDisplayDelay > 25)
	{
		FPSTxt.setString("FPS: " + std::to_string(FPS));
		FPSDisplayDelay = 0.0;
	}
	FPSDisplayDelay += deltaTime * DT_MULTIPLIER;

	this->pollEvents();

	this->gameInfo.setString("Kills: " + std::to_string(player->kills));
	if (player->HP > 0)
	{
		for (auto& heart : HPBar)
		{

		}
		for (auto& oneFire : fire)
		{
			this->fireAnimation->update(0, deltaTime);
			oneFire.setTextureRect(fireAnimation->uvRect);
		}

		static double emnemySpawnDelay = 0;
		if (emnemySpawnDelay > 100 && enemies.size() < 3)
		{
			float enemySpawnChanceSum[5];
			std::copy(enemySpawnChance, enemySpawnChance + 5, enemySpawnChanceSum);

			short r = rand() % 100;
			short enemyLevel = 0;

			for (size_t i = 0; i < 5; i++)
			{
				if (i != 0)
				{
					enemySpawnChanceSum[i] += enemySpawnChanceSum[i - 1];
				}
			}
			bool isAlreadyTaken = false;
			for (size_t i = 0; i < 5; i++)
			{
				if (isAlreadyTaken == false && r < enemySpawnChanceSum[i])
				{
					isAlreadyTaken = true;
					enemyLevel = static_cast<int>(i);
				}
			}


			float enemySpawnOffset = 500;
			float enemyPositionX = static_cast<float>(rand() % (static_cast<int>(sf::VideoMode::getDesktopMode().width + enemySpawnOffset)) - enemySpawnOffset);
			this->enemies.push_back(Enemy{ enemyPositionX, -enemySpawnOffset, enemiesTextures[enemyLevel], &font2, enemyLevel });
			//this->enemies.push_back(Enemy{ 1000.f, 500.f, &enemy3Texture, 3 });
			emnemySpawnDelay = 0;
		}
		emnemySpawnDelay += deltaTime * DT_MULTIPLIER;

		int enemyNum = 0;

		for (auto& enemy : enemies)
		{
			enemy.update(this->window, this->player->shape.getGlobalBounds(), deltaTime);

			int ballNum = 0;
			for (auto& ball : balls)
			{
				if ((fabs(enemy.shape.getPosition().x + 25 - ball.shape.getPosition().x) < 40) && (fabs(enemy.shape.getPosition().y + 25 - ball.shape.getPosition().y) < 40))
				{
					// enemy has been shot
					balls.erase(balls.begin() + ballNum);
					enemy.HP--;
					this->hitShots++;


					if (enemy.HP <= 0)
					{
						enemies.erase(enemies.begin() + enemyNum);
						player->kills++;
						if (player->kills < 100) // zwiêkszanie szansy na wylosowanie trudniejszego przeciwnika i zmniejszanie szansy na lepszego
						{
							this->enemySpawnChance[0] -= 38.f / 100.f;
							this->enemySpawnChance[1] -= 20.f / 100.f;
							this->enemySpawnChance[3] += 20.f / 100.f;
							this->enemySpawnChance[4] += 38.f / 100.f;
						}

					}

					//break;

				}

				ballNum++;

			}
			if (fabs(player->shape.getPosition().x - enemy.shape.getPosition().x) < 50 && fabs(player->shape.getPosition().y - enemy.shape.getPosition().y) < 50)
			{
				player->kills++;
				if (player->kills < 100) // zwiêkszanie szansy na wylosowanie trudniejszego przeciwnika i zmniejszanie szansy na lepszego
				{
					this->enemySpawnChance[0] -= 38.f / 100.f;
					this->enemySpawnChance[1] -= 20.f / 100.f;
					this->enemySpawnChance[3] += 20.f / 100.f;
					this->enemySpawnChance[4] += 38.f / 100.f;
				}
				player->HP--; // Dodaæ jakiœ offset czasowy, bo gdy dotykam przeciwnika to ta p¹tle przelatuje têdy kilka razy
				this->HPBar.erase(HPBar.begin() + player->HP);
				enemies.erase(enemies.begin() + enemyNum);
			}
			enemyNum++;
		}
		for (auto& ball : balls)
		{
			ball.update(this->window, deltaTime);
			//ball.updateCollision(ball.shape.getGlobalBounds(), )
			//ball.setVelocity(Wektor{ 5.0, 5.0 });
		}
		for (auto& platformT : platforms)
		{
			platformT.update(this->window, deltaTime);
			for (auto& block : platformT.platform)
			{
				for (auto& enemy : enemies)
				{
					enemy.updateCollision(enemy.shape.getGlobalBounds(), block.shape.getGlobalBounds(), enemy, enemy.shape);
				}
				player->updateCollision(player->shape.getGlobalBounds(), block.shape.getGlobalBounds(), *player, player->shape);
				int i = 0;
				for (auto ball = balls.begin(); ball != balls.end(); ball++)
				{
					ball->updateCollision(ball->shape.getGlobalBounds(), block.shape.getGlobalBounds(), *ball, ball->shape);
					if ((fabs(ball->velocity.x) < ball->velocityMin) && (fabs(ball->velocity.y) < ball->velocityMin))
					{
						balls.erase(balls.begin() + i);
						break;
					}
					i++;

				}
			}

		}

		this->player->update(this->window, *this->window, &ballTexture, &balls, deltaTime);
	}
	else 
	{
		// Gra zakoñczona
		this->HPBar.clear();
		static double gameoverTimer = 0;
		int time = 70;
		if (gameoverTimer < time)
		{
			GAMEOVER.setFillColor(sf::Color::Red);
		}
		if (gameoverTimer >= time)
		{
			GAMEOVER.setFillColor(sf::Color::Transparent);
		}
		if (gameoverTimer >= 2 * time)
		{

			gameoverTimer = 0;
		}
		gameoverTimer += deltaTime * DT_MULTIPLIER;
		
	}



}

//void Game::updateCollision()
//{
//	for (auto& platformT : platforms)
//	{
//		for (auto& block : platformT.platform)
//		{
//			if (block.shape.getGlobalBounds().intersects(player->shape.getGlobalBounds()))
//			{
//				std::cout << "COLLISION!\n";
//			}
//		}
//	}
//}

void Game::render()
{
	this->window->clear();
	this->window->draw(background_sprite);


	//this->block1.render(this->window);
	//this->block1.setIsRigid(false);
	for (auto& enemy : enemies)
	{
		enemy.render(this->window);
	}
	for (auto& ball : balls)
	{
		ball.render(this->window);
	}

	for (size_t i = 0; i < this->platforms.size(); i++)
	{
		this->platforms.at(i).render(this->window);

	}

	this->player->render(this->window);

	for (auto& oneFire : fire)
	{
		window->draw(oneFire);
	}

	for (auto& heart : HPBar)
	{
		window->draw(heart);
	}

	this->window->draw(gameInfo);
	this->window->draw(FPSTxt);

	if (player->HP <= 0)
	{
		this->scoreTxt.setString("Score: " + std::to_string(player->kills));
		this->bestScoreTxt.setString("Best score: " + std::to_string(bestScore));
		if(player->totalShots != 0)
			this->accuracyTxt.setString("Accuracy: " + std::to_string(static_cast<int>(hitShots * 100.f / player->totalShots)) + "%");

		this->window->draw(GAMEOVER);
		this->window->draw(scoreTxt);
		this->window->draw(bestScoreTxt);
		this->window->draw(accuracyTxt);
	}
	this->window->display();
}

int Game::getBestScore() const
{
	return this->bestScore;
}

void Game::setBestScore(int score)
{
	this->bestScore = score;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		default:
			break;
		}
	}
}
