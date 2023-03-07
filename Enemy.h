#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Body.h"

class Enemy : public Body
{
public:
	Enemy(sf::Font* font);
	Enemy(float positionX, float positionY, sf::Texture* texture, sf::Font* font, short level);
	~Enemy();

	void update(const sf::RenderTarget* target, const sf::FloatRect playerBounds, float deltaTime);
	void render(sf::RenderTarget* target);
	void calculateMovement(const sf::FloatRect playerBounds, float deltaTime);
	void spawnEnemy();

	sf::Sprite shape;
	int HP;
private:

	sf::Text HPTxt;
	int HPMax;
	float speed;

};

