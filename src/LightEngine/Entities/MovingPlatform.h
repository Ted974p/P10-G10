#pragma once
#include "PlatformEntity.h"
#include "../RectangleCollider.h"

class MovingPlatform : public PlatformEntity  
{
private:
	sf::Clock movingTimer;
	bool movingStarted = false;
	const float MOVING_DELAY = 4.0f;

public:

	virtual void onInitialize() override;
	virtual void onUpdate() override;


	virtual void onColliding(Entity* _other) override;
};

