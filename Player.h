#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Body.h"
#include "Ball.h"

class Player : public Body
{
public:
	//Constructors & Destructors
	Player(float posX, float posY, bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY, sf::Texture* texture, sf::Texture* gunTexture);
	Player(float posX, float posY);
	Player();
	virtual ~Player();

	// Public functions
	void update(const sf::RenderTarget* target, const sf::Window& window, sf::Texture* ballTexture, std::vector<Ball>* balls, float deltaTime);
	void updateInput();
	void updateGun(const sf::Window& window, const sf::RenderTarget* target, sf::Texture* ballTexture, std::vector<Ball>* balls, float deltaTime);
	void render(sf::RenderTarget* target);
	void updateWindowBoundsCollision(const sf::RenderTarget* target, sf::Sprite& shape);

	sf::Sprite shape;
	sf::Sprite gun;
	int HP;
	int kills;
	int totalShots;
private:

	int HPMax;
	double ballVelocity;
	sf::Vector2i mousePosition;
	sf::Vector2f mousePosView;
	double movementSpeed;
	void initVariables();
	//void initShape();
	void initPhysicalParameters(bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY);
};

