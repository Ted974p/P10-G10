#pragma once
#include "../Entity.h"

class Animator;
class DoorEntity;

class ButtonEntity : public Entity
{
	DoorEntity* door;
public:

	virtual void onInitialize() override;
	void onLeftCollision(Entity* other);
};

