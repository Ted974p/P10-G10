
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
	float mLandingDeceleration = 150.f;  
	bool mJustLanded = false;            
	float mLandingTimer = 0.f;           
	const float LANDING_DECELERATION_TIME = 1.f;

	/*LiftableEntity* mLiftedObject;*/

	bool isInLightEntity = false;
	sf::Clock AnnimTimer;
	sf::Clock lightTimer;
	bool speedBoostActive = false;
	LiftableEntity* mLiftedObject;

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

	virtual void updateCameraWithDeadzones();
	virtual void jump();
	virtual void onDownCollision(Entity* other) override;
	virtual void onUpCollision(Entity* other) override;
};
