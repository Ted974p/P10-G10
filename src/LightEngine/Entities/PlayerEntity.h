#pragma once
#include "../Entity.h"

class LiftableEntity;

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
		Drop,
		Count
	};


	static constexpr int StateCount = static_cast<int>(State::Count);


private:
	State mState = State::Idle;

	int mTransitions[StateCount][StateCount] =
	{
		{1,1,1,1,1,1}, // Idle
		{1,1,1,1,1,1}, // Running
		{1,1,1,1,1,1}, // Jumping
		{1,1,1,1,1,1}, // Morphing
		{1,1,1,1,1,1}, // Wearing
		{1,1,1,1,1,1}  // Drop
	};

private: 
	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce = 12;

	bool isInLightEntity = false;
	sf::Clock AnnimTimer;
	sf::Clock lightTimer;
	bool speedBoostActive = false;
	LiftableEntity* mLiftedObject;
	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

public:

	LiftableEntity* GetLiftedObject() { return mLiftedObject; }
	void setLiftedObject(LiftableEntity* liftedObj) { mLiftedObject = liftedObj; }
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
	//void Drop();
	virtual void onDownCollision(Entity* other);

	virtual void onCollisionEnter(Entity* other) { std::cout << "enter" << std::endl; }
	virtual void onCollisionExit(Entity* other) { std::cout << "exit" << std::endl; }
};

