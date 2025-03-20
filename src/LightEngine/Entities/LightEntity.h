#pragma once
#include "../Entity.h"

class LightEntity : public Entity
{

	SpriteSheet* mSpriteSheet3;
	Animator* mAnimator3;
public:

	virtual void onInitialize() override;
	virtual void onCollision(Entity* other) override;
	virtual void onUpdate() override {};
};

