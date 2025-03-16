#pragma once
#include "../Entity.h"

class LvPlatformEntity : public Entity
{

public:
	void onInitialize() override;
	void set(int x, int y);
};

