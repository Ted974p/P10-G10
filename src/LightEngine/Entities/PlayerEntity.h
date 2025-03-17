#pragma once
#include "../Entity.h"
#include "SFML/Graphics.hpp"

class PlayerEntity : public Entity
{
public:
	enum class State
	{
		Idle,
		Running,
		Jumping,
		Morphing,
		Wearing,
		Count
	};


	static constexpr int StateCount = static_cast<int>(State::Count);
	
	enum class Direction
	{
		Rigth,
		Left
	};
private:
	State mState = State::Idle;

	int mTransitions[StateCount][StateCount] =
	{
		{0,1,1,1,1},
		{1,0,1,1,1},
		{1,1,0,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0}
	};
	private: 

		int mdirection;
	bool isMovingRight;
	bool isMovingLeft;
	bool isJumping = false;

	sf::Clock* Timer;
private:

	float mJumpForce = 12;

public:

	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	virtual void onUpdate() override;
	bool SetStates(State State);
private:


	virtual void jump();
	void onDownCollision() override;
};

