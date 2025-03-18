#pragma once
#include "../Entity.h"
#include "DoorEntity.h"

class ButtonEntity : public Entity
{
	DoorEntity* door;
	sf::Clock closingTimer;
	bool closingStarted = false;
	const float DOOR_CLOSE_DELAY = 5.0f;
public:
	virtual void onInitialize() override;
	void SetDoor(DoorEntity* doorEntity);
	virtual void onCollision(Entity* other) override;
	virtual void onUpdate() override;
};

