#pragma once

#include <SFML/Graphics.hpp>

#include "Body.h"

class Ball : public Body
{
public:
	Ball(float positionX, float positionY, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double velocityX, double velocityY, sf::Texture* texture);
	~Ball();

	sf::Sprite shape;
	void update(const sf::RenderTarget* target, float deltaTime);
	void render(sf::RenderTarget* target);
	void updatePhysics(sf::Sprite& target, float deltaTime);

private:
	//double velocity;
	Wektor direction;

};

