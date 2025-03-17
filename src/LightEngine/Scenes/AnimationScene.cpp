#include "AnimationScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/ObstacleEntity.h"
#include "../Entities/PlatformEntity.h"
#include "../Entities/ButtonEntity.h"
#include "../Entities/DoorEntity.h"

#include "../CircleCollider.h"
#include "../RectangleCollider.h"

#include "../Utils/Debug.h"

#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include <iostream>

void AnimationScene::onInitialize()
{
	player = createEntity<PlayerEntity>();
	player->setPosition(0, 650);

	obstacle = createEntity<ObstacleEntity>();
    obstacle->setPosition(200, 100);

	door = createEntity<DoorEntity>();
	door->setPosition(600, 500);

	button = createEntity<ButtonEntity>();
	button->setPosition(0, 550);
	button->SetDoor(door);

    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 700);
}