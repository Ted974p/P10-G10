#pragma once
#include "../Entity.h"

class LiftableEntity;

class PlayerHead : public Entity
{

	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce = 12;

	bool isInLightEntity = false;
	sf::Clock lightTimer;
	bool speedBoostActive = false;
	LiftableEntity* mLiftedObject;
	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

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
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;

private:

	virtual void jump();
	virtual void onDownCollision(Entity* other);
	virtual void checkIfGrounded();
};

