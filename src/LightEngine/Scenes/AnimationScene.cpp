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
	player->setPosition(200, 250);

	obstacle = createEntity<ObstacleEntity>();
    obstacle->setPosition(200, 100);
	obstacle->setRigidBody(true);

	button = createEntity<ButtonEntity>();
	button->setPosition(600, 400);
	button->onLeftCollision(other);

	door = createEntity<DoorEntity>();
	door->setPosition(900, 300);

    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 700);
}



