#include "Player.h"

//Constructors & Destructors
Player::Player()
{
	this->shape.setPosition(0.f, 0.f);
	this->initVariables();
	this->initShape();
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();

	this->setVelocity(Wektor(10.0, 10.0));
}

Player::~Player()
{
}

// Private functions

void Player::initVariables()
{
	this->movementSpeed = 5.0;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));

}

void Player::initPhysicalParameters(bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY)
{
	this->isRigid = _isRigid;
}

// Public functions

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	this->updatePhysics(this->shape);
	this->setIsOnGround(false);
	this->updateWindowBoundsCollision(target, this->shape);
}

void Player::updateInput()
{
	bool PressedW = false;
	bool PressedS = false;
	bool PressedA = false;
	bool PressedD = false;
	// Keyboard input
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!PressedA)
		{
			PressedA = true;
			this->velocity.x = -movementSpeed;
			//this->setVelocity(Wektor{ -movementSpeed, 0.0 });
		}
	}
	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!PressedD)
		{
			PressedD = true;
			this->velocity.x = movementSpeed;
		}
	}
	// Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{

	}
	// Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (!PressedS)
			if (!isOnGround)
				this->velocity.y = movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (isOnGround)
			this->velocity.y = this->velocity.y - 7.8;
	}
}



void Player::render(sf::RenderTarget* target)
{


	target->draw(this->shape);
}

double Player::getAcceleration(short xy) const
{
	return xy == 0 ? this->acceleration.x : this->acceleration.y;
}

double Player::getVelocity(short xy) const
{
	return xy == 0 ? this->velocity.x : this->velocity.y;
}

double Player::getForce(short xy) const
{
	return xy == 0 ? this->force.x : this->force.y;
}

double Player::getMovement(short xy) const
{
	return xy == 0 ? this->movement.x : this->movement.y;
}