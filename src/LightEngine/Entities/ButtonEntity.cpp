#include "ButtonEntity.h"

#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include "../Scenes/AnimationScene.h"

#include <iostream>

void ButtonEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(false);
	setKinetic(false);
}

void ButtonEntity::SetDoor(DoorEntity* doorEntity)
{
    door = doorEntity;
}

void ButtonEntity::onColliding(Entity* other)
{
    std::cout << "collision";

    if (other->isTag((int)Entity::TAG::Player)) {
        std::cout << "Player detected in collision!" << std::endl;
        door->goToPosition(300.f, 300.f, 5.f);
    }
    else {
        std::cout << "This is not the player!" << std::endl;
    }
}