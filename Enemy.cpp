#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(float positionX, float positionY, sf::Texture* texture, short level)
{
	this->shape.setPosition(sf::Vector2f(positionX, positionY));
	this->shape.setScale(1.25, 1.25);
	this->shape.setTexture(*texture);

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
		this->speed = 4.f;
		break;
	default:
		break;
	}

}

Enemy::~Enemy()
{
}

void Enemy::update(const sf::RenderTarget* target, const sf::FloatRect playerBounds)
{
	this->calculateMovement(playerBounds);
	this->updatePhysics(this->shape);
	//this->updateWindowBoundsCollision(target, this->shape);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Enemy::calculateMovement(const sf::FloatRect playerBounds)
{
	sf::FloatRect enemyBounds = this->shape.getGlobalBounds();

	double b = atan2f(playerBounds.top - enemyBounds.top, playerBounds.left - enemyBounds.left) * 180 / M_PI;

	float movementX = static_cast<float>(this->speed * cos(b * M_PI / 180));
	float movementY = static_cast<float>(this->speed * sin(b * M_PI / 180));

	//this->shape.move(movementX, movementY);
	this->setVelocity(Wektor{ movementX, movementY });
}

void Enemy::spawnEnemy()
{

}
