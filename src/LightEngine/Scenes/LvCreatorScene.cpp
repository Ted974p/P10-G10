#include "LvCreatorScene.h"
#include "../LvlMaker.h"
#include "../Entities/PlayerEntity.h"
#include "../Entities/EmptyEntity.h"
#include "../Entities/LvPlatformEntity.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define COLLUMS 60
#define ROWS 14
#define SIZE 100

void LvCreatorScene::onInitialize()
{

}

void LvCreatorScene::LevelMaker(std::vector<char> sight, std::vector<Position> positions)
{
	for (size_t i = 0; i < sight.size(); ++i)
	{


		char s = sight[i];
		Position pos = positions[i];

		int posx = SIZE * pos.x;
		int posy = -700 + SIZE * pos.y;
		if (s == 'D')
		{
			platform = createEntity<LvPlatformEntity>();
			platform->set(posx, posy);


		}
		if (s == '-')
		{
			entity = createEntity<EmptyEntity>();
			entity->set(posx, posy);

		}

	}
}

void LvCreatorScene::onEvent(const sf::Event& event)
{
}

void LvCreatorScene::onUpdate()
{
}
