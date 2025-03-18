#pragma once
#include "../Entity.h"

class Animator;

class ObstacleEntity : public Entity
{
private:

	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

public:

	virtual void onInitialize() override;
	virtual void onDownCollision(Entity* _other) override;
	void checkIfGrounded();
	virtual void onUpdate() override;
};