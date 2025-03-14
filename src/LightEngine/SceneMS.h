#pragma once

#include "Scene.h"
#include "Player.h"
#include "Plateformer.h"
#include <SFML/Graphics/View.hpp>

class SceneMS : public Scene
{
	Plateformer* pPlateformer;
	Entity* pEntity1;
	Entity* pEntity2;

	Player* mPlayer;

private:

	sf::View mView;

public:
	void onInitialize() override;
	void onEvent(const sf::Event& event) override;
	void onUpdate() override;
};

