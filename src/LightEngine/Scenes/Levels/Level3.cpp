#include "Level3.h"

#include "../../Managers/GameManager.h"
#include "Level4.h"

#include "../../Entities/ActivablePlatform.h"
#include "../../Entities/ButtonEntity.h"
#include "../../Entities/DoorEntity.h"

void Level3::setNameLevel()
{
	mNameLevel = "Level3";
}

void Level3::editEntitiesCreated()
{
	for (ActivablePlatform* platform : platforms)
	{
		platform->setDirection(0, 1);
		platform->setDistance(3 * 64);
		platform->setSpeed(10);
		platform->setActive(false);
		buttons[1]->AddActivableEntity(platform);
	}
	for (DoorEntity* door : doors)
	{
		buttons[0]->AddActivableEntity(door);
	}

	buttons[1]->setActivationDuration(10);
	buttons[0]->setActivationDuration(12);
}

void Level3::goToNextLevel()
{
	exit(0);
	gameManager->LaunchScene<Level4>();
}


