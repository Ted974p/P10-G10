#include "MovingPlatform.h"
#include "TargetEntity.h"

#include "../Managers/ResourceManager.h"
#include "../Rendering/SpriteSheet.h"

#include <iostream>


void MovingPlatform::onInitialize()
{
    movingTowardsTarget = true;

    setSpeed(30);
    originalPosition = getPosition();  // Stocke la position d'origine

    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
    setRigidBody(true);
    setKinetic(false);
    setTag(int(Entity::TAG::Button));

    sf::Texture* texture1 = resourceManager->GetTexture("props");
    if (!texture1) {
        std::cerr << "Erreur : Impossible de charger la texture 'props'." << std::endl;
    }
    mSpriteSheet = new SpriteSheet(texture1, 4, 6);
    mSpriteSheet->setPosition(32, 32);
    mSpriteSheet->setScale(0.64f, 0.64f);
    mSpriteSheet->setCurrent(9);
}

void MovingPlatform::onUpdate()
{
    if (targetEntity == nullptr)
        return;

    sf::Vector2f targetPosition = movingTowardsTarget ? targetEntity->getPosition() : originalPosition;

    std::cout << movingTowardsTarget << std::endl;

    if (goToPosition(targetPosition.x, targetPosition.y, mSpeed))
    {
        movingTowardsTarget = false;
        movingTimer.restart();
    }
}

void MovingPlatform::onCollision(Entity* _other)
{
    if (_other->isTag((int)Entity::TAG::Plateform))
    {
        movingTowardsTarget = false; // Change la direction lors d'une collision
        movingTimer.restart();
    }
}
