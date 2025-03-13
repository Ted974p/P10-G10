#pragma once
#include "../Entity.h"

class PlayerEntity : public Entity
{
public:

	virtual void onInitialize() override;
	virtual void onUpdate() override;
};

