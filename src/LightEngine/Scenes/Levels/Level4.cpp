#include "Level4.h"

#include "../../Managers/GameManager.h"
#include "Level1.h"

#include "../../Entities/MovingPlatform.h"
#include "../../Entities/ButtonEntity.h"
#include "../../Entities/DoorEntity.h"

void Level4::setNameLevel()
{
	mNameLevel = "Level4";
}

void Level4::editEntitiesCreated()
{
	buttons[0]->setActivationDuration(20.f);

	for (DoorEntity* door : doors)
		buttons[0]->AddActivableEntity(door);
}

void Level4::goToNextLevel()
{
	exit(0);
	gameManager->LaunchScene<Level1>();
}
