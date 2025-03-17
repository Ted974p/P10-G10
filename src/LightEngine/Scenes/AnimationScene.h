#pragma once

#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;
class LiftableEntity;

class AnimationScene : public Scene
{

public:

	PlayerEntity* player;
	ObstacleEntity* obstacle;
	PlatformEntity* ground;
	LiftableEntity* liftable;


	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override {};
};


