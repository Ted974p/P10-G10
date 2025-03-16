#include "LvCreatorScene.h"

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
	LevelMaker();
}

void LvCreatorScene::LevelMaker()
{
	std::ifstream EditorFile("../../../src/LightEngine/Assets/lvl.txt");
	std::string line;
	std::vector<std::vector<char>> list;
	if (EditorFile.is_open()) 
	{
		while (std::getline(EditorFile, line)) 
		{
			list.push_back(std::vector<char>(line.begin(), line.end()));
		}
	}
	else {
		std::cout << "Erreur d'ouverture ";
	}
	EditorFile.close();

	
	for (int x = 0; x < ROWS;x++)
	{
		for (int y = 0; y < COLLUMS; y++)
		{
			int posx = SIZE * x;
			int posy = -700 + SIZE * y;
			std::cout << list[x][y];
			if (list[x][y]== '-')
			{
				//entity = createEntity<EmptyEntity>();
				//entity->set(posx, posy);
			}
			if (list[x][y] == 'D')
			{
				platform = createEntity<LvPlatformEntity>();
				platform->set(posx, posy);
			}
		}	
		std::cout << std::endl;
	}

}

void LvCreatorScene::onEvent(const sf::Event& event)
{
}

void LvCreatorScene::onUpdate()
{
}
