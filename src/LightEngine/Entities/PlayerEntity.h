#pragma once
#include "../Entity.h"
#include "SFML/Graphics.hpp"

class PlayerEntity : public Entity
{

private: 

	bool isMovingRight;
	bool isMovingLeft;
	bool isJumping = false;
	bool isruning = false;
	sf::Clock* Timer;
private:

	float mJumpForce = 12;

public:

	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	virtual void onUpdate() override;

private:


	virtual void jump();
	void onDownCollision() override;
};

