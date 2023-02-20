#include "Game.h"

Game::Game()
{
	this->initWindow();
	
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

bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::update()
{
	this->pollEvents();
	this->player.update(this->window);
}

void Game::render()
{
	this->window->clear();

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
