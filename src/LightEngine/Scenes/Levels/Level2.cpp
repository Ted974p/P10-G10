#include "Level2.h"

#include "../../Entities/MovingPlatform.h"
#include "../../Entities/ButtonEntity.h"
#include "../../Entities/DoorEntity.h"
#include "../../Entities/TargetEntity.h"

void Level2::setNameLevel()
{
	mNameLevel = "level2";
}

void Level2::editEntitiesCreated()
{
	platforms[0]->setTargetEntity(targets[2]);
	platforms[1]->setTargetEntity(targets[1]);
	platforms[2]->setTargetEntity(targets[0]);

	//buttons[0]->AddActivableEntity(platforms[0])

	//buttons[0]->AddActivableEntity(platforms[0])
	//buttons[0]->AddActivableEntity(platforms[2])
}
