#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Body.h"

class Player : public Body
{
public:
	//Constructors & Destructors
	Player(float posX, float posY, bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY);
	Player(float posX, float posY);
	Player();
	virtual ~Player();

	// Public functions
	void update(const sf::RenderTarget* target);
	void updateInput();
	void render(sf::RenderTarget* target);
	//void updateWindowBoundsCollision(const sf::RenderTarget* target);

	// Getters
	//double getVelocity(short xy) const;
	//double getAcceleration(short xy) const;
	//double getMovement(short xy) const;
	//double getForce(short xy) const;

	sf::RectangleShape shape;
private:
	double movementSpeed;
	void initVariables();
	void initShape();
	void initPhysicalParameters(bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY);
};

