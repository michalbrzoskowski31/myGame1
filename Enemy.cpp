#include "Enemy.h"

Enemy::Enemy(sf::Font* font)
{
	this->HPMax = 1;
	this->HP = this->HPMax;
	this->speed = 1.f;

	//this->font = new sf::Font{ *font };
	this->HPTxt.setFont(*font);
	this->HPTxt.setCharacterSize(30);
	this->HPTxt.setFillColor(sf::Color::Black);
}

Enemy::Enemy(float positionX, float positionY, sf::Texture* texture, sf::Font* font, short level)
{
	this->shape.setPosition(sf::Vector2f(positionX, positionY));
	this->shape.setScale(1.25, 1.25);
	this->shape.setTexture(*texture);

	this->HPMax = 1;
	this->HP = this->HPMax;
	this->speed = 1.f;

	switch (level)
	{
	case 0:
		this->HPMax = 1;
		this->HP = this->HPMax;
		this->speed = 2.f;
		break;
	case 1:
		this->HPMax = 2;
		this->HP = this->HPMax;
		this->speed = 2.f;
		break;
	case 2:
		this->HPMax = 2;
		this->HP = this->HPMax;
		this->speed = 3.f;
		break;
	case 3:
		this->HPMax = 3;
		this->HP = this->HPMax;
		this->speed = 3.f;
		break;
	case 4:
		this->HPMax = 4;
		this->HP = this->HPMax;
		this->speed = 3.3f;
		break;
	default:
		break;
	}

	//this->font = new sf::Font{*font};
	this->HPTxt.setFont(*font);
	this->HPTxt.setCharacterSize(30);
	this->HPTxt.setFillColor(sf::Color::Black);

}

Enemy::~Enemy()
{
	//delete this->font;
}

void Enemy::update(const sf::RenderTarget* target, const sf::FloatRect playerBounds, float deltaTime)
{
	this->calculateMovement(playerBounds, deltaTime);
	this->updatePhysics(this->shape, deltaTime);

	this->HPTxt.setString(std::to_string(this->HP));
	int offset = 15;
	this->HPTxt.setPosition(this->shape.getPosition().x - offset, this->shape.getPosition().y - offset);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->HPTxt);
	//target->draw(this->HPBar.at(0));
}

void Enemy::calculateMovement(const sf::FloatRect playerBounds, float deltaTime)
{
	sf::FloatRect enemyBounds = this->shape.getGlobalBounds();

	double b = atan2f(playerBounds.top - enemyBounds.top, playerBounds.left - enemyBounds.left) * 180 / M_PI;
	//int multiplier = 164.7989453;

	float movementX = static_cast<float>(this->speed * cos(b * M_PI / 180)); // multiplier * deltaTime *  
	float movementY = static_cast<float>(this->speed * sin(b * M_PI / 180));
	std::cout << deltaTime << "\n";

	//this->shape.move(movementX, movementY);
	this->setVelocity(Wektor{ movementX, movementY });
}

void Enemy::spawnEnemy()
{

}
