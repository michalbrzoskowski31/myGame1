#include "Platform.h"

Platform::Platform(float positionX, float positionY, short width, short height, sf::Texture* texture)
{
	for (size_t w = 0; w < width; w++)
	{
		for (size_t h = 0; h < height; h++)
		{
			platform.push_back(Block{ positionX + w * grid, positionY + h * grid, texture});

		}
	}
}

Platform::~Platform()
{
	
}

void Platform::update(const sf::RenderTarget* target, float deltaTime)
{
	for (auto& block : platform)
	{
		block.updatePhysics(block.shape, deltaTime);
		block.updateWindowBoundsCollision(target, block.shape);
	}
}

void Platform::render(sf::RenderTarget* target)
{
	for (auto& block : platform)
	{
		target->draw(block.shape);
	}
}
