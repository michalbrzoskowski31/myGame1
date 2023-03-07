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

}

Block::Block()
	: Body(true, 0.1, 10.0, 0.1, 0.1, 0.0, 0.0)
{
	this->shape.setPosition(sf::Vector2f(0.f, 0.f));

}

Block::~Block()
{

}

void Block::update(const sf::RenderTarget* target, float deltaTime)
{
	this->updatePhysics(this->shape, deltaTime);
	this->updateWindowBoundsCollision(target, this->shape);
}

void Block::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

