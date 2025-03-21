#pragma once
#include "../Entity.h"

class DecorsEntity : public Entity
{
public:
	virtual void onInitialize() override;
	void SetCurrent();
};

