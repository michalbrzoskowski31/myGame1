#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->loadTextures();
	this->background_sprite.setTexture(backgroundTexture); // mozna to potem daæ gdzieœ indziej
	this->initStructures();

	this->player = new Player{ 1050.f, 700.f, false, 0.1, 10.0, 0.1, 0.1, 10.0, -5.0, &playerTexture };
	this->balls.push_back(Ball{ 100.f, 100.f, 0.1, 10.f, 0.3, 0.f, &ballTexture });

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
}

void Game::initStructures()
{
	//this->platform1_ptr = new Platform{ 500.f, 300.f, 7, 2, &blockGrass };
	this->platforms.push_back(Platform{ 0.f, 1030.f, 15, 1, &blockGrassTexture });
	this->platforms.push_back(Platform{ 1700.f, 500.f, 3, 5, &blockDefaultTexture });
	this->platforms.push_back(Platform{ 500.f, 900.f, 5, 1, &blockDefaultTexture });
	this->platforms.push_back(Platform{ 1000.f, 700.f, 7, 2, &blockGrassTexture });

	this->platforms.at(2).platform.at(2).setIsRigid(false);
	this->platforms.at(2).platform.at(2).setLossOfEnergy(1.01);
	this->platforms.at(2).platform.at(2).setFriction(1.01);
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
	for (auto& ball : balls)
	{
		ball.update(this->window);
	}
	for(auto& platformT : platforms)
	{
		platformT.update(this->window);
		for (auto& block : platformT.platform)
		{

			sf::FloatRect playerBounds = player->shape.getGlobalBounds();
			sf::FloatRect blockBounds = block.shape.getGlobalBounds();


			if (blockBounds.intersects(player->nextPos))
			{
				//std::cout << "COLLISION!\n";
				if (playerBounds.left < blockBounds.left
					&& playerBounds.left + playerBounds.width < blockBounds.left + blockBounds.width
					&& playerBounds.top < blockBounds.top + blockBounds.height
					&& playerBounds.top + playerBounds.height > blockBounds.top) // Right collision
				{
					player->setVelocity(Wektor{ 0, player->getVelocity().y });
					player->shape.setPosition(blockBounds.left - playerBounds.width, playerBounds.top);
				}
				else if (playerBounds.left > blockBounds.left
					&& playerBounds.left + playerBounds.width > blockBounds.left + blockBounds.width
					&& playerBounds.top < blockBounds.top + blockBounds.height
					&& playerBounds.top + playerBounds.height > blockBounds.top) // Left collision
				{
					player->setVelocity(Wektor{ 0, player->getVelocity().y });
					player->shape.setPosition(blockBounds.left + blockBounds.width, playerBounds.top);
				}
				if (playerBounds.top < blockBounds.top
					&& playerBounds.top + playerBounds.height < blockBounds.top + blockBounds.height
					&& playerBounds.left < blockBounds.left + blockBounds.width
					&& playerBounds.left + playerBounds.width > blockBounds.left) // Bottom collision
				{
					player->setIsOnGround(true);
					player->setVelocity(Wektor{ player->getVelocity().x, 0 });
					player->shape.setPosition(playerBounds.left,  blockBounds.top - playerBounds.height);
				}
				else if (playerBounds.top > blockBounds.top
					&& playerBounds.top + playerBounds.height > blockBounds.top + blockBounds.height
					&& playerBounds.left < blockBounds.left + blockBounds.width
					&& playerBounds.left + playerBounds.width > blockBounds.left) // Top collision
				{
					player->setVelocity(Wektor{ player->getVelocity().x, 0 });
					player->shape.setPosition(playerBounds.left, blockBounds.top + blockBounds.height);
				}
				
			}
		}

	}

	this->player->update(this->window);
}

void Game::updateCollision()
{
	for (auto& platformT : platforms)
	{
		for (auto& block : platformT.platform)
		{
			if (block.shape.getGlobalBounds().intersects(player->shape.getGlobalBounds()))
			{
				std::cout << "COLLISION!\n";
			}
		}
	}
}

void Game::render()
{
	this->window->clear();
	this->window->draw(background_sprite);


	//this->block1.render(this->window);
	//this->block1.setIsRigid(false);
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
