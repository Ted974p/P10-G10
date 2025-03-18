#include "LvlMaker.h"
#include "Managers/ResourceManager.h"

#include "Entities/LvPlatformEntity.h"
#include "Entities/EmptyEntity.h"

#include <fstream>
#include <iostream>

#define COLLUMS 60
#define ROWS 14
#define SIZE 100

void LvlMaker::ReadFile(std::string name)
{
	std::ifstream EditorFile(resourceManager->getPath(name));
	char sight;
	int row = 0;
	int col = 0;
	if (EditorFile.is_open())
	{
		while (EditorFile >> sight) {
			{
				m_sight.push_back(sight);
				m_positions.push_back({ col, row });
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
}

std::vector<char> LvlMaker::GetSight()
{
	return m_sight;
}

std::vector<Position> LvlMaker::GetPosition()
{
	return m_positions;
}

