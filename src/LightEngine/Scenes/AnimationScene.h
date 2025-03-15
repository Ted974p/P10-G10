#pragma once
#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;
class ButtonEntity;
class DoorEntity;

class AnimationScene : public Scene
{
	PlayerEntity* player;
	ObstacleEntity* obstacle;
	ButtonEntity* button;
	DoorEntity* door;
	PlatformEntity* ground;
	Entity* other;

public:
	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override {};
};


