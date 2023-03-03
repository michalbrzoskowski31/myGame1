#pragma once

#define _USE_MATH_DEFINES

#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Body.h"

class Enemy : public Body
{
public:
	Enemy();
	Enemy(float positionX, float positionY, sf::Texture* texture, short level);
	~Enemy();

	void update(const sf::RenderTarget* target, const sf::FloatRect playerBounds);
	void render(sf::RenderTarget* target);
	void calculateMovement(const sf::FloatRect playerBounds);
	void spawnEnemy();

	sf::Sprite shape;
	int HP;
private:
	int HPMax;
	float speed;
};

