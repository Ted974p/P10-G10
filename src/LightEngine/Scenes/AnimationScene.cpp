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
	player->setPosition(0, 650);

    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 700);

	obstacle = createEntity<ObstacleEntity>();
    obstacle->setPosition(8, 100);

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
}