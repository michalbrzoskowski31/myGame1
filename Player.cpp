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
	this->gun.setOrigin(232, 25); //232
	this->ballVelocity = 10.0;

	this->HPMax = 5;
	this->HP = this->HPMax;
	this->kills = 0;
	this->totalShots = 0;
	//this->initShape();
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	//this->initShape();

	this->HPMax = 5;
	this->HP = this->HPMax;
	this->kills = 0;

	this->setVelocity(Wektor(10.0, 10.0));
}

Player::Player()
	: Body(false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
{
	this->shape.setPosition(0.f, 0.f);
	this->initVariables();
	this->kills = 0;
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

void Player::update(const sf::RenderTarget* target, const sf::Window& window, sf::Texture* ballTexture, std::vector<Ball>* balls, float deltaTime)
{

	this->updateInput();
	this->updatePhysics(this->shape, deltaTime);
	this->setIsOnGround(false);
	this->updateWindowBoundsCollision(target, this->shape);
	this->updateGun(window, target, ballTexture, balls, deltaTime);
	
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

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target, sf::Sprite& shape)
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
		this->HP = 0;


		//velocity.x = 0;
		//velocity.y = 0;

	}
}

void Player::updateGun(const sf::Window& window, const sf::RenderTarget* target, sf::Texture* ballTexture, std::vector<Ball>* balls, float deltaTime)
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



	double b = atan2f(point1.x - point2.x, point1.y - point2.y) * 180 / M_PI -90;
	if (mousePosition.x > shape.getPosition().x)
	{
		this->gun.setScale(0.25, -0.25);
	}
	else
	{
		this->gun.setScale(0.25, 0.25);
	}
	this->gun.setRotation(static_cast<float>(b));
	
	static double shotDelay = 0;

	int spreadAngle = 5;
	int spread = rand() % (2 * spreadAngle) - spreadAngle;

	if (shotDelay > 25 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->totalShots++;
		int correction = 180;
		double velocityX = ballVelocity * cos((b + correction + spread) * M_PI / 180);
		double velocityY = ballVelocity * sin((b + correction + spread) * M_PI / 180);
		//std::cout << b + 270 << "   cos(b + 270) = " << cos(b + 270) <<  "   ==> x = " << ballVelocity * cos(b + 270) << "\n";
		balls->push_back(Ball{this->shape.getPosition().x, this->shape.getPosition().y, 0.05, 10, 0.3, 0.99, velocityX, velocityY, ballTexture});
		shotDelay = 0;
	}
	shotDelay += deltaTime * DT_MULTIPLIER;
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