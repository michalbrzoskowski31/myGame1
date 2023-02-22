#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->loadTextures();
	this->background_sprite.setTexture(background); // mozna to potem daæ gdzieœ indziej
	this->initStructures();
}

Game::~Game()
{
	delete this->window;
}

// Inits

void Game::initWindow()
{
	this->videoMode = sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
	this->window = new sf::RenderWindow{ this->videoMode, "myGame1", sf::Style::Fullscreen };
	this->window->setFramerateLimit(144);
}

void Game::loadTextures()
{
	this->blockDefault.loadFromFile("Textures/block_ground.png");
	this->blockGrass.loadFromFile("Textures/block_grass.png");
	this->background.loadFromFile("Textures/background.png");
}

void Game::initStructures()
{
	//this->platform1_ptr = new Platform{ 500.f, 300.f, 7, 2, &blockGrass };
	this->platforms.push_back(new Platform{ 0.f, 1030.f, 15, 1, &blockGrass });
	this->platforms.push_back(new Platform{ 1700.f, 500.f, 3, 5, &blockDefault });
	this->platforms.push_back(new Platform{ 500.f, 900.f, 5, 1, &blockDefault });

	this->platforms.at(2)->platform.at(2).setIsRigid(false);
	this->platforms.at(2)->platform.at(2).setLossOfEnergy(1.01);
	this->platforms.at(2)->platform.at(2).setFriction(1.01);
}

bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::update()
{
	this->pollEvents();

	this->block1.update(this->window);

	for (size_t i = 0; i < this->platforms.size(); i++)
	{
		this->platforms.at(i)->update(this->window);

	}

	this->player.update(this->window);
}

void Game::render()
{
	this->window->clear();
	this->window->draw(background_sprite);


	this->block1.render(this->window);
	//this->block1.setIsRigid(false);

	for (size_t i = 0; i < this->platforms.size(); i++)
	{
		this->platforms.at(i)->render(this->window);

	}

	this->player.render(this->window);

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
