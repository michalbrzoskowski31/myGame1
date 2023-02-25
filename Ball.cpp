#include "Ball.h"

Ball::Ball(float positionX, float positionY, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, sf::Texture* texture)
	: Body(false, _gravityForce, _mass, _lossOfEnergy, _friction, 0.0, 0.0)
{
	this->shape.setPosition(positionX, positionY);
	this->shape.setTexture(*texture);
	this->velocity = 7.5;

}

Ball::~Ball()
{
}

void Ball::update(const sf::RenderTarget* target)
{
	this->updatePhysics(this->shape);
	this->updateWindowBoundsCollision(target, this->shape);
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
