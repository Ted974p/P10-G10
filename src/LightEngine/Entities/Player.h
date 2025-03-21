
#pragma once
#include "../Entity.h"

class LiftableEntity;
class PlayerHead;

class Player : public Entity
{

public:
	enum class State
	{
		Idle,
		Running,
		Jumping,
		Morphing,
		DeMorphing,
		Lifting,
		Drop,
		Count
	};


	static constexpr int StateCount = static_cast<int>(State::Count);


private:
	State mState = State::Idle;

	int mTransitions[StateCount][StateCount] =
	{
		{0,1,1,1,1,1,0},
		{1,0,1,0,0,1,0},
		{1,1,0,0,0,0,0},
		{0,0,0,0,1,0,0},
		{1,0,0,0,0,0,0},
		{0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0}
	};

private:

	std::string mCurrentAnimation;
	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce = 12;
	bool closingStarted = false;
	float mLandingDeceleration = 150.f;
	bool mJustLanded = false;
	float mLandingTimer = 0.f;
	bool Morf = false;

	sf::Clock AnnimFlower;
	sf::Clock MorphingTime;
	bool isInLightEntity = false;
	bool speedBoostActive = false;
	LiftableEntity* mLiftedObject;
	PlayerHead* head;

public:

	LiftableEntity* GetLiftedObject() { return mLiftedObject; }
	void setLiftedObject(LiftableEntity* liftedObj) { mLiftedObject = liftedObj; mState = State::Lifting; }
	bool SetStates(State State);
	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	void setInLightEntity(bool value);
	virtual void onUpdate() override;
	void setMaxSpeed(float speed) { mMaxSpeed = speed; }
	void Morphing();
	void DeMorphing();
	void robotDesactivate();
	void robotActivation();
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;

private:

	virtual void updateCameraWithDeadzones();
	virtual void jump();
	void Drop();
	virtual void onDownCollision(Entity* other) override;

	virtual void onCollisionEnter(Entity* other) {}
	virtual void onCollisionExit(Entity* other) {}
	virtual void onUpCollision(Entity* other) override;

};