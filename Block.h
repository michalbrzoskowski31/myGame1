#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Body.h"

class Block : public Body
{
public:
	Block(float positionX, float positionY, sf::Texture* texture);
	Block(float positionX, float positionY);
	Block();
	~Block();


	//void initBlock();
	void update(const sf::RenderTarget* target, float deltaTime);
	void render(sf::RenderTarget* target);
	void initTexture();

	sf::Sprite shape;
	sf::Texture textureDefault;
	sf::Vector2i position;
	int grid = 50;
};

