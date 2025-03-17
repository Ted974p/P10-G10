#include "AnimationScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/ObstacleEntity.h"
#include "../Entities/PlatformEntity.h"
#include "../Entities/LiftableEntity.h"

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

    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 700);

	/*obstacle = createEntity<ObstacleEntity>();
    obstacle->setPosition(8, 100);*/


	liftable = createEntity<LiftableEntity>();
	liftable->setPosition(300, 100);

}