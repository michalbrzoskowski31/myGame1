#include "Ball.h"

Ball::Ball(float positionX, float positionY, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double velocityX, double velocityY, sf::Texture* texture)
	: Body(false, _gravityForce, _mass, _lossOfEnergy, _friction, velocityX, velocityY)
{
	//this->velocity = 7.5;
	this->shape.setPosition(positionX, positionY);
	this->shape.setTexture(*texture);
	this->shape.setScale(0.8f, 0.8f);

}

Ball::~Ball()
{
}

void Ball::update(const sf::RenderTarget* target, float deltaTime)
{
	this->updatePhysics(this->shape, deltaTime);
	this->updateWindowBoundsCollision(target, this->shape);
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Ball::updatePhysics(sf::Sprite& target, float deltaTime)
{
	if (!isRigid)
	{
		updateAcceleration(deltaTime);
		updateForce();
		updateVelocity();
		updateMovement(target, deltaTime);
		updateNextPosition(target.getGlobalBounds());

		if (isOnGround)
		{
			if (fabs(velocity.x) <= velocityMin)
			{
				velocity.x = 0;
			}
			else
				velocity.x = velocity.x * friction;

		}
	}

}
