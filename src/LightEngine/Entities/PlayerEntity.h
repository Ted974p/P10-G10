#pragma once
#include "../Entity.h"

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
	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce = 12;

	bool isInLightEntity = false;
	sf::Clock AnnimTimer;
	sf::Clock lightTimer;
	bool speedBoostActive = false;

	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

public:
	bool SetStates(State State);
	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	void setInLightEntity(bool value);
	virtual void onUpdate() override;
	void setMaxSpeed(float speed) { mMaxSpeed = speed; }

private:

	virtual void jump();
	virtual void onDownCollision(Entity* other);
	virtual void checkIfGrounded();
};

