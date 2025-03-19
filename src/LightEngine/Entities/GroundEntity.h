#pragma once
#include "../Entity.h"

class  SpriteSheet;
class GroundEntity :public Entity
{
private:
		SpriteSheet* mSpriteSheet2;
public:

	virtual void onInitialize() override;
};

