#include "AnimationScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/ObstacleEntity.h"
#include "../Entities/PlatformEntity.h"
#include "../Entities/MovingPlatform.h"
#include "../Entities/ButtonEntity.h"
#include "../Entities/DoorEntity.h"
#include "../Entities/LightEntity.h"

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
	player->setPosition(0, 650);
	
	gameManager->getParallax()->setPlayer(player);

	obstacle = createEntity<ObstacleEntity>();
    obstacle->setPosition(600, 400);

	door = createEntity<DoorEntity>();
	door->setPosition(600, 400);

	button = createEntity<ButtonEntity>();
	button->setPosition(400, 550);
	button->SetDoor(door);

	//light = createEntity<LightEntity>();
	//light->setPosition(400, 550);

    platform = createEntity<MovingPlatform>();
    platform->setPosition(-300, 700);

    mView.setSize(GameManager::GetInstance()->GetWindow()->getSize().x, GameManager::GetInstance()->GetWindow()->getSize().y);
    mView.setCenter(player->getPosition());

}

void AnimationScene::onUpdate()
{
    
    
    sf::Vector2f targetPosition = player->getPosition();
    sf::Vector2f currentViewPosition = mView.getCenter();


    float smoothFactor = 5.0f * getDeltaTime();
    mView.setCenter(currentViewPosition + (targetPosition - currentViewPosition) * smoothFactor);

    
    GameManager* gm = GameManager::GetInstance();
    if (gm)
    {
        sf::RenderWindow* window = gm->GetWindow();
        if (window)
        {
            window->setView(mView);
        }
    }
    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 1050);
}