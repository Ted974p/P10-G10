#pragma once

#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;
class MovingPlatform;
class ButtonEntity;
class DoorEntity;
class LightEntity;
class LightEntity2;
class PlayerBody;
class PlayerHead;
class LiftableEntity;
class Camera;

class AnimationScene : public Scene
{
public:

	Camera* mCamera;

	LightEntity* light;
	LightEntity2* light2;
	PlayerEntity* player;
	ObstacleEntity* obstacle;
	ObstacleEntity* obstacle2;
	ButtonEntity* button;
	PlatformEntity* ground;
	MovingPlatform* platform;
	LiftableEntity* liftable;

	DoorEntity* door;
	PlayerBody* body;
	PlayerHead* head;

	Camera* getCamera();
	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override;
};


