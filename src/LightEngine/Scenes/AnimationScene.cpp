#include "AnimationScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/ObstacleEntity.h"
#include "../Entities/PlatformEntity.h"

#include "../CircleCollider.h"
#include "../RectangleCollider.h"

#include "../Utils/Debug.h"

#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include <iostream>

void AnimationScene::onInitialize()
{


	player = createEntity<PlayerEntity>();
	player->setPosition(0, 300);

	obstacle = createEntity<ObstacleEntity>();
    obstacle->setPosition(200, 100);

    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 700);
}