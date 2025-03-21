#include "Level4.h"
#include "../../Entities/MovingPlatform.h"
#include "../../Entities/ButtonEntity.h"
#include "../../Entities/DoorEntity.h"

void Level4::setNameLevel()
{
	mNameLevel = "Level4.1";
}

void Level4::editEntitiesCreated()
{
	//buttons[1]->setActivationDuration(3);

	//for (MovingPlatform* plat : platforms)
	//	buttons[1]->AddActivableEntity(plat);

	buttons[1]->setActivationDuration(30.f);

	for (DoorEntity* door : doors)
		buttons[1]->AddActivableEntity(door);
}
