#pragma once
#include "../Entity.h"

class LiftableEntity;
class PlayerEntity;

class Head : public Entity
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
		{0,1,1,1,1},
		{1,0,1,1,1},
		{1,1,0,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0}
	};

	std::string mCurrentAnimation;
	bool isMovingRight;
	bool isMovingLeft;
	bool Demorfing;
	float mJumpForce = 12;
	sf::Clock closingTimer;
	bool mJustLanded = false;
	float mLandingTimer = 0.f;



	/*LiftableEntity* mLiftedObject;*/

	bool isInLightEntity = false;

	bool speedBoostActive = false;

public:
	PlayerEntity* PlayerBody;

	bool SetStates(State State);
	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	void setInLightEntity(bool value);
	virtual void onUpdate() override;
	void setMaxSpeed(float speed) { mMaxSpeed = speed; }
	void Set(PlayerEntity* player);
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;

private:

	virtual void updateCameraWithDeadzones();
	virtual void jump();
	virtual void onDownCollision(Entity* other) override;
	void onCollisionEnter(Entity* other) override;
	virtual void onCollisionExit(Entity* other) override;
};

