#pragma once
#include "../Entity.h"
#include "DoorEntity.h"

class ButtonEntity : public Entity
{
	DoorEntity* door;
public:
	virtual void onInitialize() override;
	void SetDoor(DoorEntity* doorEntity);
	virtual void onColliding(Entity* other);
	virtual void onUpdate() override {};
};

