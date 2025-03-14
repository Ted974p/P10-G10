#pragma once
#include "../Entity.h"

class PlayerEntity : public Entity
{
private:

	float mJumpForce = 16;

public:

	virtual void onInitialize() override;
	virtual void onUpdate() override;

private:


	virtual void jump();
	virtual void onDownCollision();
};

