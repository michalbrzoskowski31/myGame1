#include "Player.h"

//Constructors & Destructors
Player::Player(float posX/*position X*/, float posY, bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY, sf::Texture* playerTexture, sf::Texture* gunTexture)
	: Body(_isRigid, _gravityForce, _mass, _lossOfEnergy, _friction, _velocityX, _velocityY)
{
	
	this->shape.setPosition(posX, posY);
	this->initVariables();
	this->shape.setTexture(*playerTexture);
	this->gun.setTexture(*gunTexture);
	this->gun.setScale(0.25, 0.25);
	this->gun.setOrigin(232, 0);
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

void Player::update(const sf::RenderTarget* target, const sf::Window& window)
{

	this->updateInput();
	this->updatePhysics(this->shape);
	this->setIsOnGround(false);
	this->updateWindowBoundsCollision(target, this->shape);
	this->updateGun(window, target);
	
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
		if (1)
		{
			PressedA = true;
			this->velocity.x = -movementSpeed;
			//this->setVelocity(Wektor{ -movementSpeed, 0.0 });
		}
	}
	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (1)
		{
			PressedD = true;
			this->velocity.x = movementSpeed;
		}
	}
	// Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->velocity.y = -movementSpeed;
	}
	// Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (!PressedS)
			//if (!isOnGround)
				this->velocity.y = movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (isOnGround)
			this->velocity.y = this->velocity.y - 7.8;
	}
}

void Player::updateGun(const sf::Window& window, const sf::RenderTarget* target)
{
	this->gun.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
	this->mousePosition = sf::Mouse::getPosition(window);
	this->mousePosView = target->mapPixelToCoords(this->mousePosition);
	sf::Vector2f point1;
	point1.x = (shape.getPosition().x - (window.getSize().x / 2));
	point1.y = (window.getSize().y) / 2 - shape.getPosition().y;

	sf::Vector2f point2;
	point2.x = (mousePosView.x - (window.getSize().x / 2));
	point2.y = (window.getSize().y) / 2 - mousePosView.y;

	float b = atan2f(point1.x - point2.x, point1.y - point2.y) * 180 / 3.141592653 -90;
	if (mousePosition.x > shape.getPosition().x)
	{
		this->gun.setScale(0.25, -0.25);
		//this->gun.setRotation(b);
	}
	else
	{
		this->gun.setScale(0.25, 0.25);
	}
	this->gun.setRotation(b);
	std::cout << b << "\n";

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//balls.push_back(Ball{ shape.getPosition().x, shape.getPosition().y, 0.1, 10, 0.2, 0.2, &texture});
	}
}



void Player::render(sf::RenderTarget* target)
{


	target->draw(this->shape);
	target->draw(this->gun);
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