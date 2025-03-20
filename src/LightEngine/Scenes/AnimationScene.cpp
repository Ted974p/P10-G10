#include "AnimationScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/ObstacleEntity.h"
#include "../Entities/PlatformEntity.h"
#include "../Entities/MovingPlatform.h"
#include "../Entities/ButtonEntity.h"
#include "../Entities/DoorEntity.h"
#include "../Entities/LightEntity.h"
#include "../Entities/LightEntity2.h"
#include "../Entities/PlayerBody.h"
#include "../Entities/PlayerHead.h"
#include "../Entities/LiftableEntity.h"

#include "../CircleCollider.h"
#include "../RectangleCollider.h"

#include "../Utils/Debug.h"

#include "../Rendering/Background.h"
#include "../Rendering/Parallax.h"
#include "../Rendering/Camera.h"

#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include <iostream>

Camera* AnimationScene::getCamera()
{
	return mCamera;
}

void AnimationScene::onInitialize()
{
	Background* background_sky = createBackground();
	background_sky->setTexture("bg_sky");
	background_sky->setSpeed(1);

	Background* background3 = createBackground();
	background3->setTexture("bg_layer3");
	background3->setSpeed(3);

	Background* background2 = createBackground();
	background2->setTexture("bg_layer2");
	background2->setSpeed(2);

	Background* background1 = createBackground();
	background1->setTexture("bg_layer1");
	background1->setSpeed(3);

	player = createEntity<PlayerEntity>();
	player->setPosition(200, 650);

	//body = createEntity<PlayerBody>();
	//body->setPosition(0, 650);

	//head = createEntity < PlayerHead>();
	//head->setPosition(0, 650);

	gameManager->getParallax()->setPlayer(player);

	//obstacle = createEntity<ObstacleEntity>();
    //obstacle->setPosition(600, 400);

	//obstacle2 = createEntity<ObstacleEntity>();
	//obstacle2->setPosition(900, 900);

	door = createEntity<DoorEntity>();
	door->setPosition(600, 900);

	button = createEntity<ButtonEntity>();
	button->setPosition(400, 900);
	button->SetDoor(door);

	liftable = createEntity<LiftableEntity>();
	liftable->setPosition(200, 200);

	light2 = createEntity<LightEntity2>();
	light2->setPosition(0, 0);

    platform = createEntity<MovingPlatform>();
    platform->setPosition(-300, 1050);

	ground = createEntity<PlatformEntity>();
	ground->setPosition(0, 1050);

	// setCamera
	mCamera = new Camera();

	GameManager* gm = gameManager;
	mCamera->setSize(gm->GetWindowWidth() * 0.8f, gm->GetWindowHeight() * 0.8f);
	mCamera->setDeadzone(300, 300, -50, 50);
	mCamera->setLimits(0, 1920, 0, 1080);
	mCamera->setCenter(mCamera->getSize().x / 2, player->getPosition().y);
}

void AnimationScene::onUpdate()
{
	mCamera->update(gameManager->GetDeltaTime());
	gameManager->GetWindow()->setView(*mCamera);
}
