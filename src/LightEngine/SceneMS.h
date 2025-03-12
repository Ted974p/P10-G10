#pragma once

#include "Scene.h"
#include "Player.h"
#include <SFML/Graphics/View.hpp>

class SceneMS : public Scene
{
	Entity* pEntity1;
	Entity* pEntity2;

	Player* mPlayer;

private:

	sf::View mView;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

