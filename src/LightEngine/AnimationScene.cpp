#include "AnimationScene.h"

#include "PlayerEntity.h"
#include "ObstacleEntity.h"
#include "PlatformEntity.h"

#include "CircleCollider.h"
#include "RectangleCollider.h"

#include "Utils/Debug.h"

#include "Managers/GameManager.h"
#include "Managers/InputManager.h"
#include <iostream>

void AnimationScene::OnInitialize()
{
	player = createEntity<PlayerEntity>(sf::Color::Red);
	player->setPosition(0, 0);

	obstacle = createEntity<ObstacleEntity>(sf::Color::Green);
    obstacle->setPosition(200, 100);

    ground = createEntity<PlatformEntity>(sf::Color::Red);
    ground->setPosition(0, 700);
}