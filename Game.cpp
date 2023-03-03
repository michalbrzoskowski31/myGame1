#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->loadTextures();
	this->background_sprite.setTexture(backgroundTexture); // mozna to potem daæ gdzieœ indziej
	this->initStructures();

	this->player = new Player{ 1050.f, 700.f, false, 0.1, 10.0, 0.1, 0.1, 10.0, -5.0, &playerTexture, &gunTexture};
	//this->balls.push_back(Ball{ 100.f, 100.f, 0.1, 10.f, 0.3, 0.f, &ballTexture });

}

Game::~Game()
{
	delete this->window;
}

// Inits

void Game::initWindow()
{
	//sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height  <-- wymiary okna
	this->videoMode = sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
	this->window = new sf::RenderWindow{ this->videoMode, "myGame1", sf::Style::Fullscreen };
	this->window->setFramerateLimit(144);
}

void Game::loadTextures()
{
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
}

void Game::initStructures()
{
	//this->platform1_ptr = new Platform{ 500.f, 300.f, 7, 2, &blockGrass };
	this->platforms.push_back(Platform{ 0.f, 1030.f, 15, 1, &blockGrassTexture });
	this->platforms.push_back(Platform{ 1700.f, 500.f, 3, 5, &blockDefaultTexture });
	this->platforms.push_back(Platform{ 500.f, 900.f, 5, 1, &blockDefaultTexture });
	this->platforms.push_back(Platform{ 1000.f, 700.f, 1, 7, &blockGrassTexture });

	this->platforms.at(2).platform.at(2).setIsRigid(false);
	this->platforms.at(2).platform.at(2).setLossOfEnergy(1.0);
	this->platforms.at(2).platform.at(2).setFriction(1.0);

	//this->enemies.push_back(Enemy{ 1000.f, 500.f, &enemy1Texture });
}

bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::update()
{
	this->pollEvents();

	//this->block1.update(this->window);

	//for (size_t i = 0; i < this->platforms.size(); i++)

	/*
	* Kolizja po prawej stronie gracza nie dzia³a
	*/

	static int emnemySpawnDelay = 0;
	if (emnemySpawnDelay > 100 && enemies.size() < 3)
	{
		short enemyLevel = rand() % 5;
		float enemySpawnOffset = 500;
		float enemyPositionX = static_cast<float>(rand() % (static_cast<int>(sf::VideoMode::getDesktopMode().width + enemySpawnOffset)) - enemySpawnOffset);
		this->enemies.push_back(Enemy{ enemyPositionX, -enemySpawnOffset, enemiesTextures[enemyLevel], enemyLevel});
		//this->enemies.push_back(Enemy{ 1000.f, 500.f, &enemy3Texture, 3 });
		emnemySpawnDelay = 0;
	}
	emnemySpawnDelay++;

	int enemyNum = 0;

	for (auto& enemy : enemies)
	{
		enemy.update(this->window, this->player->shape.getGlobalBounds());
		int ballNum = 0;
		for (auto& ball : balls)
		{
			if ((fabs(enemy.shape.getPosition().x + 25 - ball.shape.getPosition().x) < 40) && (fabs(enemy.shape.getPosition().y + 25 - ball.shape.getPosition().y) < 40))
			{
				
				
				balls.erase(balls.begin() + ballNum);
				enemy.HP--;
				if (enemy.HP <= 0)
				{
					enemies.erase(enemies.begin() + enemyNum);

				}

				//break;
				
			}
			ballNum++;
			
		}
		enemyNum++;
	}
	for (auto& ball : balls)
	{
		ball.update(this->window);
		//ball.updateCollision(ball.shape.getGlobalBounds(), )
		//ball.setVelocity(Wektor{ 5.0, 5.0 });
	}
	for(auto& platformT : platforms)
	{
		platformT.update(this->window);
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

	this->player->update(this->window, *this->window, &ballTexture, &balls);

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

	this->window->display();
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
