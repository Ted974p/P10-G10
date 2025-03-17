#pragma once
#include "../Entity.h"

class PlayerEntity : public Entity
{

private: 

	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce = 12;

	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

public:

	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	virtual void onUpdate() override;

private:


	virtual void jump();
	virtual void onDownCollision();
	virtual void checkIfGrounded();
};

