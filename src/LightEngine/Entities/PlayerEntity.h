
#pragma once
#include "../Entity.h"
#include "LiftableEntity.h"

class PlayerEntity : public Entity
{

private:

	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce = 12;

	LiftableEntity* mLiftedObject;

	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

public:

	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	virtual void onUpdate() override;
	LiftableEntity* GetLiftedObject() { return mLiftedObject; }
	void setLiftedObject(LiftableEntity* liftedObj) { mLiftedObject = liftedObj; }

private:


	virtual void jump();
	virtual void onDownCollision(Entity* other);
	virtual void checkIfGrounded();
};
