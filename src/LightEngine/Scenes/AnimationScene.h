#pragma once

#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;

class AnimationScene : public Scene
{
	PlayerEntity* player;
	ObstacleEntity* obstacle;
	PlatformEntity* ground;



public:
	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override {};
};


