#include "Level2.h"

#include "../../Entities/MovingPlatform.h"
#include "../../Entities/ButtonEntity.h"
#include "../../Entities/DoorEntity.h"
#include "../../Entities/ActivablePlatform.h"

void Level2::setNameLevel()
{
	mNameLevel = "level2";
}

void Level2::editEntitiesCreated()
{
	platforms[1]->setDirection(0, -1);
	platforms[1]->setDistance(8 * 64);
	platforms[1]->setSpeed(50);
	platforms[1]->setLoop(true);
	platforms[1]->setActive(true);

	platforms[0]->setDirection(1, 0);
	platforms[0]->setDistance(15 * 64);
	platforms[0]->setSpeed(95);
	platforms[0]->setLoop(false);
	platforms[0]->setActive(false);

	platforms[2]->setDirection(0, -1);
	platforms[2]->setDistance(8 * 64);
	platforms[2]->setSpeed(50);
	platforms[2]->setLoop(false);
	platforms[2]->setActive(false);

	buttons[0]->setActivationDuration(30);
	buttons[0]->AddActivableEntity(platforms[0]);
	buttons[0]->AddActivableEntity(platforms[2]);
}
