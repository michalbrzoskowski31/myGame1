#include "Platform.h"

Platform::Platform(float positionX, float positionY, short width, short height)
{
	//initBlocksTextures();
	this->blockDefault.loadFromFile("C:\\Users\\Micha\\Desktop\\Programowanie\\C++\\myGame1\\Textures\\block_ground.png");
	for (size_t i = 0; i < width; i++)
	{
		platform.push_back(Block{ positionX + i * grid, positionY , &blockDefault});
	}
}

Platform::~Platform()
{
	
}

void Platform::update(const sf::RenderTarget* target)
{
	for (size_t i = 0; i < 5; i++)
	{
		this->platform.at(i).updatePhysics(this->platform.at(i).shape);
		this->platform.at(i).updateWindowBoundsCollision(target, this->platform.at(i).shape);
	}
}

void Platform::render(sf::RenderTarget* target)
{
	for (size_t i = 0; i < platform.size(); i++)
	{
		target->draw(platform.at(i).shape);
	}
}
