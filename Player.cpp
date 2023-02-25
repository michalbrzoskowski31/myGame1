#include "Player.h"

//Constructors & Destructors
Player::Player(float posX/*position X*/, float posY, bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY, sf::Texture* texture)
	: Body(_isRigid, _gravityForce, _mass, _lossOfEnergy, _friction, _velocityX, _velocityY)
{
	
	this->shape.setPosition(posX, posY);
	this->initVariables();
	this->shape.setTexture(*texture);
	//this->shape.setScale(0.95, 0.95);
	//this->initShape();
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	//this->initShape();

	this->setVelocity(Wektor(10.0, 10.0));
}

Player::Player()
	: Body(false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
{
	this->shape.setPosition(0.f, 0.f);
	this->initVariables();
	//this->initShape();
}

Player::~Player()
{
}

// Private functions

void Player::initVariables()
{
	this->movementSpeed = 3.0;
}

//void Player::initShape()
//{
//	this->shape.setFillColor(sf::Color::Green);
//	this->shape.setSize(sf::Vector2f(50.f, 50.f));
//
//}

void Player::initPhysicalParameters(bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY)
{
	this->isRigid = _isRigid;
}

// Public functions

void Player::update(const sf::RenderTarget* target)
{

	this->updatePhysics(this->shape);
	this->setIsOnGround(false);
	this->updateWindowBoundsCollision(target, this->shape);
	this->updateInput();

	//this->updateCollidingStates();
}

void Player::updateInput()
{
	// Keyboard input
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!leftColliding)
		{
			this->velocity.x = -movementSpeed;
			//this->setVelocity(Wektor{ -movementSpeed, 0.0 });
		}
	}
	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!rightColliding)
		{
			this->velocity.x = movementSpeed;

		}
	}
	// Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if(!topColliding)
			this->velocity.y = -movementSpeed;
	}
	// Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{

		if (!bottomColliding)
			this->velocity.y = movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (isOnGround)
			this->velocity.y = this->velocity.y - 7.8;
	}
	//rightColliding = false;
	//leftColliding = false;
}



void Player::render(sf::RenderTarget* target)
{


	target->draw(this->shape);
}

//double Player::getAcceleration(short xy) const
//{
//	return xy == 0 ? this->acceleration.x : this->acceleration.y;
//}
//
//double Player::getVelocity(short xy) const
//{
//	return xy == 0 ? this->velocity.x : this->velocity.y;
//}
//
//double Player::getForce(short xy) const
//{
//	return xy == 0 ? this->force.x : this->force.y;
//}
//
//double Player::getMovement(short xy) const
//{
//	return xy == 0 ? this->movement.x : this->movement.y;
//}