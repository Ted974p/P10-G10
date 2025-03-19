#include "LvCreatorScene.h"
#include "../Managers/ResourceManager.h"

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
	levelMaker("lvl");

}

void LvCreatorScene::levelMaker(std::string name)
{
	std::ifstream EditorFile(resourceManager->getPath(name));
	char sight;
	int row = 0;
	int col = 0;
	if (EditorFile.is_open())
	{
		while (EditorFile >> sight) {
			{
				mSight.push_back(sight);
				mPositions.push_back({ col, row });
			}
			col++;
			if (col >= COLLUMS)
			{
				col = 0;
				row++;
			}
		}
	}
	else
	{
		std::cout << "Erreur d'ouverture ";
	}
	EditorFile.close();
	for (size_t i = 0; i < mSight.size(); ++i)
	{


		char s = mSight[i];
		Position pos = mPositions[i];

		int posx = SIZE * pos.x;
		int posy = -700 + SIZE * pos.y;
		if (s == 'D')
		{
			platform = createEntity<LvPlatformEntity>();
			platform->set(posx, posy);
		}
		if (s == 'P')
		{
			player = createEntity<PlayerEntity>();
			player->setPosition(posx, posy);
		}
		if (s == '-')
		{
		

		}

	}
}





void LvCreatorScene::onEvent(const sf::Event& event)
{
}

void LvCreatorScene::onUpdate()
{
}
