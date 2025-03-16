#pragma once
#include "../Scene.h"

class PlayerEntity;
class EmptyEntity;
class LvPlatformEntity;

class LvCreatorScene: public Scene
{
public:
	PlayerEntity* player;
	EmptyEntity* entity;
	LvPlatformEntity* platform;
	void onInitialize() override;
	void LevelMaker();

	// Hérité via Scene
	void onEvent(const sf::Event& event) override;
	void onUpdate() override;
};

