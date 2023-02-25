#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Wektor.h"

//#define DELTA_V(hold_v, current_v) current_v - hold_v

class Body
{
public:

	// constructors & destructors
	Body();
	//Body(bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY)
	//	: isRigid(_isRigid), gravityForce(_gravityForce), mass(_mass), lossOfEnergy(_lossOfEnergy), friction(_friction), velocity(_velocityX, _velocityY);
	
	Body(bool _isRigid, double _gravityForce, double _mass, double _lossOfEnergy, double _friction, double _velocityX, double _velocityY);
	~Body();

	// Update
		void updatePhysics(sf::Sprite& target);
		void updatePhysics(sf::Shape& target);

		void updateAcceleration();
		void updateForce();
		void updateVelocity();

		void updateMovement(sf::Sprite& target);
		void updateMovement(sf::Shape& target);
		void updateWindowBoundsCollision(const sf::RenderTarget* target, sf::Sprite& shape);
		void updateWindowBoundsCollision(const sf::RenderTarget* target, sf::Shape& shape);

		void updateCollision(const sf::RenderTarget* target, sf::FloatRect body1, sf::FloatRect body2);

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

	enum coordinates {
		X = 0,
		Y,
	};

	sf::FloatRect nextPos;

	bool isRigid;
	bool isOnGround;
	double gravityForce;
	double mass;
	double lossOfEnergy;
	double friction;
	double velocityMin;

	Wektor force;

	Wektor velocity;
	Wektor holdVelocity;

	Wektor acceleration;

	Wektor movement;
};

