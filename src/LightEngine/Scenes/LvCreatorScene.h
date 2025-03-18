#pragma once
#include "../Scene.h"

class PlayerEntity;
class EmptyEntity;
class LvPlatformEntity;
class LvlMaker;
struct Position {
	int x;
	int y;
};
class LvCreatorScene: public Scene
{
public:
	LvlMaker* lvMaker;
	PlayerEntity* player;
	EmptyEntity* entity;
	LvPlatformEntity* platform;
	void onInitialize() override;
	void LevelMaker(std::vector<char> sight, std::vector<Position> position);

	// Hérité via Scene
	void onEvent(const sf::Event& event) override;
	void onUpdate() override;
};

