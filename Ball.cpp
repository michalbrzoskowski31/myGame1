#include "Ball.h"

Ball::Ball(float positionX, float positionY, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double velocityX, double velocityY, sf::Texture* texture)
	: Body(false, _gravityForce, _mass, _lossOfEnergy, _friction, velocityX, velocityY)
{
	//this->velocity = 7.5;
	this->shape.setPosition(positionX, positionY);
	this->shape.setTexture(*texture);
	this->shape.setScale(0.8, 0.8);

}

Ball::~Ball()
{
}

void Ball::update(const sf::RenderTarget* target)
{
	this->updatePhysics(this->shape);
	//if (this->velocity.x != 0 && this->velocity.y != 0)
	this->updateWindowBoundsCollision(target, this->shape);
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Ball::updatePhysics(sf::Sprite& target)
{
	if (!isRigid)
	{
		updateAcceleration();
		updateForce();
		updateVelocity();
		updateMovement(target);
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
