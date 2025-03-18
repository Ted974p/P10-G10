
#pragma once
#include "../Entity.h"

class LiftableEntity;

class PlayerEntity : public Entity
{

private:

	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce = 12;
	float mLandingDeceleration = 200.f;  
	bool mJustLanded = false;            
	float mLandingTimer = 0.f;           
	const float LANDING_DECELERATION_TIME = 0.2f;

	/*LiftableEntity* mLiftedObject;*/

	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

public:

	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	virtual void onUpdate() override;
	/*LiftableEntity* GetLiftedObject() { return mLiftedObject; }
	void setLiftedObject(LiftableEntity* liftedObj) { mLiftedObject = liftedObj; }*/

private:


	virtual void jump();
	virtual void onDownCollision(Entity* other);
	virtual void checkIfGrounded();
};
