#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Body.h"

class Ball : public Body
{
public:
	Ball(float positionX, float positionY, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, sf::Texture* texture);
	~Ball();

	sf::Sprite shape;
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

private:
	double velocity;

};

