#pragma once
#include "Entity.h"

class PlayerEntity : public Entity
{
public:

	virtual void OnInitialize() override;
	virtual void OnUpdate() override;
};

