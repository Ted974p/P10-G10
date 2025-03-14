#pragma once
#include "../Entity.h"

class PlayerEntity : public Entity
{
private:

	float mJumpForce = 5;

public:

	virtual void onInitialize() override;
	virtual void onUpdate() override;

private:


	virtual void jump();
	void onDownCollision() override;
};

