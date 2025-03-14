#include "ButtonEntity.h"

#include "../Managers/ResourceManager.h"
#include "../RectangleCollider.h"
#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include "../Entities/DoorEntity.h"

#include <iostream>

void ButtonEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(30, 30)));
    setRigidBody(false);
    setKinetic(false);
}

void DoorEntity::Move(float deltaX, float deltaY) {
    sf::Vector2f currentPosition = getPosition();
    setPosition(currentPosition.x + deltaX, currentPosition.y + deltaY);
}

void ButtonEntity::onLeftCollision(Entity* other)
{
    if (other && other->isTag(int(Entity::TAG::Player))) {
        if (door != nullptr) {
            door->Move(500.f, 500.f);
        }
        else {
            std::cerr << "Erreur: porte non initialisée !" << std::endl;
        }
    }
}

