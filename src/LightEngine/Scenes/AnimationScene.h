#pragma once

#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;
class MovingPlatform;
class ButtonEntity;
class DoorEntity;
class LightEntity;
class PlayerBody;
class PlayerHead;

class AnimationScene : public Scene
{

private:

	sf::View mView;

public:

	LightEntity* light;
	PlayerEntity* player;
	ObstacleEntity* obstacle;
	ButtonEntity* button;
	PlatformEntity* ground;
	MovingPlatform* platform;


	DoorEntity* door;
	PlayerBody* body;
	PlayerHead* head;

	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override;
};


