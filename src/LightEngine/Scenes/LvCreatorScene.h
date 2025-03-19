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
private:
	std::vector<char> mSight;
	std::vector<Position> mPositions;
public:
	LvlMaker* lvMaker;
	PlayerEntity* player;
	EmptyEntity* entity;
	LvPlatformEntity* platform;
	void onInitialize() override;
	void levelMaker(std::string name);


	// Hérité via Scene
	void onEvent(const sf::Event& event) override;
	void onUpdate() override;
};

