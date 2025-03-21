#pragma once
#include "../Entity.h"

class WallEntity :public Entity
{
public:
	virtual void onInitialize() override;
	virtual void setSkin(int _skin);
};

