#pragma once
#include"Entity.h"

class LvPlatformEntity;

struct Position {
	int x;
	int y;
};
class LvlMaker
{
protected:
	std::vector<char> m_sight;
	std::vector<Position> m_positions;

	PlayerEntity* player;
	LvPlatformEntity platform;
	void ReadFile(std::string name);
	std::vector<char> GetSight();
	std::vector<Position> GetPosition();
};

