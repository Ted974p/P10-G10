#pragma once

#include "Scene.h"
#include "Player.h"

class DummyEntity;

class SceneMS : public Scene
{
	Entity* pEntity1;
	Entity* pEntity2;

	Player* mPlayer;

private:


public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

