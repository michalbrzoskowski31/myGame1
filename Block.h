#pragma once

#include <SFML/Graphics.hpp>

#include "Body.h"

class Block : public Body
{
public:
	Block(float positionX, float positionY, sf::Texture* texture);
	Block(float positionX, float positionY);
	Block();
	~Block();


	void update(const sf::RenderTarget* target, float deltaTime);
	void render(sf::RenderTarget* target);


	sf::Sprite shape;
	sf::Texture textureDefault;
	sf::Vector2i position;
	int grid = 50;
};

