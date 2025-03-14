#pragma once

#include "../Scene.h"

class DummyEntity;

class PhysicsScene : public Scene
{
	DummyEntity* pEntity1;
	DummyEntity* pEntity2;

public:
	void onInitialize() override;
	void onEvent(const sf::Event& event) override;
	void onUpdate() override;
};


