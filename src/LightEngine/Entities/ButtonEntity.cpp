#include "ButtonEntity.h"

#include "../Managers/ResourceManager.h"
#include "../RectangleCollider.h"
#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include "../Entities/DoorEntity.h"

#include <iostream>

void ButtonEntity::setDoor(DoorEntity* doorEntity)
{
    door = doorEntity;
}

void ButtonEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    setRigidBody(true);
    setKinetic(false);
}

void ButtonEntity::onColliding(Entity* other)
{
    if (other->isTag(int(Entity::TAG::Player))) {
        std::cout << "touché" << std::endl;
        door->move(700.f, 700.f);
    }
}

