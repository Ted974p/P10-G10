#include "Level1.h"
 
#include "../../Managers/GameManager.h"
#include "Level2.h"

#include "../../Entities/MovingPlatform.h"
#include "../../Entities/ButtonEntity.h"
#include "../../Entities/DoorEntity.h"

void Level1::setNameLevel()
{
	mNameLevel = "level1";
}

void Level1::editEntitiesCreated()
{
	buttons[0]->setActivationDuration(2);

	for (DoorEntity* door : doors)
		buttons[0]->AddActivableEntity(door);
}

void Level1::goToNextLevel()
{
	exit(0);
	gameManager->LaunchScene<Level2>();
}
