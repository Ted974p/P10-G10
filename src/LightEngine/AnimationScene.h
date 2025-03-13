#pragma once

#include "Scene.h"

class PlayerEntity;
class ObstacleEntity;
class PlatformEntity;

class AnimationScene : public Scene
{
	PlayerEntity* player;
	ObstacleEntity* obstacle;
	PlatformEntity* ground;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override {};
	void OnUpdate() override {};
};


