#include "Platform.h"

Platform::Platform(float positionX, float positionY, short width, short height, sf::Texture* texture)
{
	//initBlocksTextures();
	//this->blockDefault.loadFromFile("Textures/block_ground.png");
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

void Platform::update(const sf::RenderTarget* target)
{
	for (auto& block : platform)
	{
		//this->platform.at(i).updatePhysics(this->platform.at(i).shape);
		//this->platform.at(i).updateWindowBoundsCollision(target, this->platform.at(i).shape);
		block.updatePhysics(block.shape);
		block.updateWindowBoundsCollision(target, block.shape);
	}
}

void Platform::render(sf::RenderTarget* target)
{
	for (auto& block : platform)
	{
		//target->draw(platform.at(block).shape);
		target->draw(block.shape);
	}
}
