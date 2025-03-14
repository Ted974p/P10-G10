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
	player->setPosition(200, 250);

	obstacle = createEntity<ObstacleEntity>();
    obstacle->setPosition(200, 100);

	obstaclePorte = createEntity<ObstacleEntity>();
	obstaclePorte->setPosition(400, 200);

	obstacleButton = createEntity<ObstacleEntity>();
	obstacleButton->setPosition(600, 500);

    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 700);
}

void AnimationScene::Collision()
{
	if (player->processCollision(obstacleButton))
	{
		std::cout << "touché" << std::endl;

		obstaclePorte->move(500.f, 700.f);
	}
}


