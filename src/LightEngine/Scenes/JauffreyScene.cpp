#include "JauffreyScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/PlatformEntity.h"
#include "../Entities/ButtonEntity.h"
#include "../Entities/DoorEntity.h"

#include "../CircleCollider.h"
#include "../RectangleCollider.h"

#include "../Utils/Debug.h"

#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include <iostream>

void JauffreyScene::onInitialize()
{
    player = createEntity<PlayerEntity>();
    player->setPosition(200, 250);

    door = createEntity<DoorEntity>();  
    door->setPosition(900, 300);

    button = createEntity<ButtonEntity>();
    button->setPosition(600, 400);
    button->setDoor(door);

    ground = createEntity<PlatformEntity>();
    ground->setPosition(0, 700);
}

