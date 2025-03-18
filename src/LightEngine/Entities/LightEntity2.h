#pragma once
#include "../Entity.h"

class LightEntity2 : public Entity
{
	SpriteSheet* mSpriteSheet3;
	Animator* mAnimator3;
public:

	virtual void onInitialize() override;
	virtual void onUpdate() override;
};


