#pragma once
#include "../Scene.h"

class PlayerEntity;
class PlatformEntity;
class ButtonEntity;
class DoorEntity;

class JauffreyScene : public Scene
{

public:

	PlayerEntity* player;
	ButtonEntity* button;
	DoorEntity* door;
	PlatformEntity* ground;
	Entity* other;

	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override {};
};


