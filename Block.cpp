#include "Block.h"

Block::Block(float positionX, float positionY, sf::Texture* texture)
	: Body(true, 0.1, 10.0, 0.1, 0.1, 0.0, 0.0)
{
	this->shape.setPosition(sf::Vector2f(positionX, positionY));
	this->shape.setTexture(*texture);
}

Block::Block(float positionX, float positionY)
	: Body(true, 0.1, 10.0, 0.1, 0.1, 0.0, 0.0)
{
	this->shape.setPosition(sf::Vector2f(positionX, positionY));
	this->initTexture();
}

Block::Block()
	: Body(true, 0.1, 10.0, 0.1, 0.1, 0.0, 0.0)
{
	this->shape.setPosition(sf::Vector2f(0.f, 0.f));
	this->initTexture();
}

Block::~Block()
{

}

void Block::update(const sf::RenderTarget* target)
{
	this->updatePhysics(this->shape);
	this->updateWindowBoundsCollision(target, this->shape);
}

void Block::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Block::initTexture()
{
	//this->textureDefault.loadFromFile("C:\\Users\\Micha\\Desktop\\Programowanie\\C++\\myGame1\\Textures\\block_ground.png");
	//this->shape.setTexture(textureDefault);
}

