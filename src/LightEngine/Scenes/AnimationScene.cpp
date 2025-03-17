#include "AnimationScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/ObstacleEntity.h"
#include "../Entities/PlatformEntity.h"

#include "../CircleCollider.h"
#include "../RectangleCollider.h"

#include "../Utils/Debug.h"

#include "../Rendering/Parallax.h"
#include "../Rendering/Background.h"

#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include <iostream>

void AnimationScene::onInitialize()
{
	Background* background1 = createBackground();
	background1->setTexture("bg_sky");
	background1->setSpeed(1);


	Background* background2 = createBackground();
	background2->setTexture("bg_layer2");
	background2->setSpeed(2);

	Background* background3 = createBackground();
	background3->setTexture("bg_layer1");
	background3->setSpeed(3);

	player = createEntity<PlayerEntity>();
	player->setPosition(0, 650);

	gameManager->getParallax()->setPlayer(player);

	obstacle = createEntity<ObstacleEntity>();
    obstacle->setPosition(200, 100);

    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 1050);
}