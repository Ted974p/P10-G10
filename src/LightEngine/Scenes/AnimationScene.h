#pragma once

#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;

class AnimationScene : public Scene
{

public:

	PlayerEntity* player;
	ObstacleEntity* obstacle;
	PlatformEntity* ground;
	PlatformEntity* invisiblewallRigth;

	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override {};
};


