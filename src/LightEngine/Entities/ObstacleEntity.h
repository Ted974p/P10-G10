#pragma once
#include "../Entity.h"

class Animator;

class ObstacleEntity : public Entity
{
public:

	virtual void onInitialize() override;
	virtual void onDownCollision() override;
};

