#include "Body.h"


Body::Body()
{
	this->lossOfEnergy = 0.0;
	this->friction = 0.0;
	this->mass = 0.0;
	this->velocityMin = 0.15;
	this->isRigid = false;
	this->isOnGround = false;
	this->gravityForce = 0.0;
}

//Body::Body(bool _isRigid = false, double _gravityForce = 0.0, double _mass = 1, double _lossOfEnergy = 1.0, double _friction = 1, double _velocityX = 0, double _velocityY = 0)
//	: isRigid(_isRigid), gravityForce(_gravityForce), mass(_mass), lossOfEnergy(_lossOfEnergy), friction(_friction), velocity(_velocityX, _velocityY)
//{
//	this->velocityMin = 0.15;
//	this->isOnGround = false;
//}

Body::~Body()
{
}

// Update
	void Body::updatePhysics(sf::Shape& target)
	{
		if (!isRigid)
		{
			updateAcceleration();
			updateForce();
			updateVelocity();
			updateMovement(target);

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

	void Body::updateAcceleration()
	{
		this->acceleration.y = this->gravityForce;
		this->acceleration.x = 0;
	}

	void Body::updateForce()
	{
	}

	void Body::updateVelocity()
	{
		this->velocity = this->velocity + this->acceleration;
	}

	void Body::updateMovement(sf::Shape& target)
	{
		target.move(static_cast<float>(this->velocity.x), static_cast<float>(this->velocity.y));
	}

	void Body::updateWindowBoundsCollision(const sf::RenderTarget* target, sf::Shape& shape)
	{
		// Left
		//sf::FloatRect this->shape.getGlobalBounds() = this->shape.getGlobalBounds();

		if (shape.getGlobalBounds().left <= 0.f)
		{
			shape.setPosition(0.f, shape.getGlobalBounds().top);
			velocity.x = -velocity.x * lossOfEnergy;
		}
		// Right
		if (shape.getGlobalBounds().left + shape.getGlobalBounds().width >= target->getSize().x)
		{
			shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);
			velocity.x = -velocity.x * lossOfEnergy;
		}
		// Top
		if (shape.getGlobalBounds().top <= 0.f)
		{
			shape.setPosition(shape.getGlobalBounds().left, 0.f);
			velocity.y = -velocity.y * lossOfEnergy;
		}
		// Bottom
		if (shape.getGlobalBounds().top + shape.getGlobalBounds().height >= target->getSize().y)
		{
			shape.setPosition(shape.getGlobalBounds().left, target->getSize().y - shape.getGlobalBounds().height);
			isOnGround = true;
			velocity.y = -velocity.y * lossOfEnergy;

			//velocity.x = 0;
			//velocity.y = 0;

		}
	}

// Setters
	void Body::setIsRigid(bool _isRigid)
	{
		this->isRigid = _isRigid;
	}

	void Body::setIsOnGround(bool _isOnGround)
	{
		this->isOnGround = _isOnGround;
	}

	void Body::setGravityForce(double _gravityForce)
	{
		this->gravityForce = _gravityForce;
	}

	void Body::setMass(double _mass)
	{
		this->mass = _mass;
	}

	void Body::setLossOfEnergy(double _lossOfEnergy)
	{
		this->lossOfEnergy = _lossOfEnergy;
	}

	void Body::setFriction(double _friction)
	{
		this->friction = _friction;
	}

	void Body::setVelocityMin(double _velocityMin)
	{
		this->velocityMin = _velocityMin;
	}

	

	void Body::setForce(Wektor _force)
	{
		this->force = _force;
	}

	void Body::setVelocity(Wektor _velocity)
	{
		this->velocity = _velocity;
	}

	void Body::setHoldVelocity(Wektor _holdVelocity)
	{
		this->holdVelocity = _holdVelocity;
	}

	void Body::setAcceleration(Wektor _acceleration)
	{
		this->acceleration = _acceleration;
	}

	void Body::setMovement(Wektor _movement)
	{
		this->movement = _movement;
	}

// Getters
	double Body::getIsRigid()
	{
		return this->isRigid;
	}

	double Body::getIsOnGround()
	{
		return this->isOnGround;
	}

	double Body::getGravityForce()
	{
		return this->gravityForce;
	}

	double Body::getMass()
	{
		return this->mass;
	}

	double Body::getLossOfEnergy()
	{
		return this->lossOfEnergy;
	}

	double Body::getFriction()
	{
		return this->friction;
	}

	double Body::getVelocityMin()
	{
		return this->velocityMin;
	}



	Wektor Body::getForce()
	{
		return this->force;
	}

	Wektor Body::getVelocity()
	{
		return this->velocity;
	}

	Wektor Body::getHoldVelocity()
	{
		return this->holdVelocity;
	}

	Wektor Body::getAcceleration()
	{
		return this->acceleration;
	}

	Wektor Body::getMovement()
	{
		return this->movement;
	}