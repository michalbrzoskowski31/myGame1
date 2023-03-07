#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Wektor.h"

#define DT_MULTIPLIER 164.7989453

class Body
{
public:

	// constructors & destructors
	Body();
	
	Body(bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY);
	~Body();

	// Update
		void updatePhysics(sf::Sprite& target, float deltaTime);
		//void updatePhysics(sf::Shape& target);

		void updateAcceleration(float deltaTime);
		void updateForce();
		void updateVelocity();

		void updateMovement(sf::Sprite& target, float deltaTime);
		//void updateMovement(sf::Shape& target);
		void updateWindowBoundsCollision(const sf::RenderTarget* target, sf::Sprite& shape);
		void updateWindowBoundsCollision(const sf::RenderTarget* target, sf::Shape& shape);

		void updateCollision(const sf::FloatRect& bodyBounds1, const sf::FloatRect& bodyBounds2, Body& body, sf::Sprite& shape);

		void rightCollision();
		void leftCollision();
		void topCollision();
		void bottomCollision();

		void updateNextPosition(sf::FloatRect currentPos);
	// Setters
		void setIsRigid(bool _isRigid);
		void setIsOnGround(bool _isOnGround);
		void setGravityForce(double _gravityForce);
		void setMass(double _mass);
		void setLossOfEnergy(double _lossOfEnergy);
		void setFriction(double _friction);
		void setVelocityMin(double _velocityMin);

		void setForce(Wektor _force);
		void setVelocity(Wektor _velocity);
		void setHoldVelocity(Wektor _holdVelocity);
		void setAcceleration(Wektor _acceleration);
		void setMovement(Wektor _movement);
	// Getters
		double getIsRigid();
		double getIsOnGround();
		double getGravityForce();
		double getMass();
		double getLossOfEnergy();
		double getFriction();
		double getVelocityMin();

		Wektor getForce();
		Wektor getVelocity();
		Wektor getHoldVelocity();
		Wektor getAcceleration();
		Wektor getMovement();

//private:


	sf::FloatRect nextPos;

	bool isRigid;
	bool isOnGround;
	double gravityForce;
	double mass;
	double lossOfEnergy;
	double friction;
	double velocityMin;
	//float multiplier;

	Wektor force;

	Wektor velocity;
	Wektor holdVelocity;

	Wektor acceleration;

	Wektor movement;
};

