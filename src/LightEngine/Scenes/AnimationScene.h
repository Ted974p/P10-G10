#pragma once

#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;
class ButtonEntity;
class DoorEntity;
class LightEntity;
class LightEntity2;
class PlayerBody;
class PlayerHead;

class AnimationScene : public Scene
{

public:

	LightEntity* light;
	LightEntity2* light2;
	PlayerEntity* player;
	ObstacleEntity* obstacle;
	ObstacleEntity* obstacle2;
	ButtonEntity* button;
	PlatformEntity* ground;
	DoorEntity* door;
	PlayerBody* body;
	PlayerHead* head;

	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override {};
};


