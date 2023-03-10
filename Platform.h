#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Block.h"


class Platform : public Block
{
public:
	Platform(float positionX, float positionY, short width, short height, sf::Texture* texture);
	~Platform();

	std::vector<Block> platform;
	sf::Texture blockDefault;

	void update(const sf::RenderTarget* target, float deltaTime);
	void render(sf::RenderTarget* target);
	int grid = 50;
};

