#pragma once

#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;
class MovingPlatform;

class AnimationScene : public Scene
{

private:

	sf::View mView;

public:

	PlayerEntity* player;
	ObstacleEntity* obstacle;
	PlatformEntity* ground;
	MovingPlatform* platform;



	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override;
};


