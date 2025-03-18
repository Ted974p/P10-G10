#pragma once
#include "../Entity.h"

class LightEntity : public Entity
{

public:

	virtual void onInitialize() override;
	virtual void onCollision(Entity* other) override;
	virtual void onUpdate() override {};
};

