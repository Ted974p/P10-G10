#pragma once
#include "../Entity.h"

class LightEntity : public Entity
{

public:

	virtual void onInitialize() override;
	virtual void onColliding(Entity* other);
	virtual void onUpdate() override {};
};

