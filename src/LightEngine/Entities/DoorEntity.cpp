#include "DoorEntity.h"
#include "../RectangleCollider.h"

#include "../Managers/ResourceManager.h"

#include "../Rendering/SpriteSheet.h"

#include <iostream>

void DoorEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
    setRigidBody(false);
    setKinetic(false);
    setTag(int(Entity::TAG::Button));

    sf::Texture* texture1 = resourceManager->GetTexture("props");
    if (!texture1) {
        std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
    }
    mSpriteSheet = new SpriteSheet(texture1, 4, 6);
    mSpriteSheet->setPosition(32, 32);
    mSpriteSheet->setScale(0.64f, 0.64f);
    mSpriteSheet->setCurrent(1);
}

void DoorEntity::Activate()
{
    if (!isOpen)
    {
        isOpen = true;
        setRigidBody(false);

        mSpriteSheet->setColor(sf::Color(255, 255, 255, 150));
    }
}

void DoorEntity::Deactivate()
{
    if (isOpen)
    {
        isOpen = false;
        setRigidBody(true);

        mSpriteSheet->setColor(sf::Color(255, 255, 255, 255));
    }
}

bool DoorEntity::IsActive() const
{
    return isOpen;
}
