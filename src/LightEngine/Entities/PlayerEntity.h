#pragma once
#include "../Entity.h"

class LiftableEntity;

class PlayerEntity : public Entity
{

private: 

	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce;

	bool isInLightEntity = false;
	sf::Clock lightTimer;
	bool speedBoostActive = false;
	LiftableEntity* mLiftedObject;

public:

	LiftableEntity* GetLiftedObject() { return mLiftedObject; }
	void setLiftedObject(LiftableEntity* liftedObj) { mLiftedObject = liftedObj; }
	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	void setInLightEntity(bool value);
	virtual void onUpdate() override;
	void setMaxSpeed(float speed) { mMaxSpeed = speed; }

private:

	virtual void jump();
	virtual void onDownCollision(Entity* other) override;
};

