#include "DoorEntity.h"
#include "../RectangleCollider.h"

#include <iostream>

void DoorEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    setRigidBody(true);
}

void DoorEntity::Activate()
{
    if (!isOpen)
    {
        isOpen = true;
        setRigidBody(false);

        //if (mSpriteSheet)
            //mSpriteSheet->setCurrent(0);
    }
}

void DoorEntity::Deactivate()
{
    if (isOpen)
    {
        isOpen = false;
        setRigidBody(true);

        //if (mSpriteSheet)
            //mSpriteSheet->setCurrent(1);
    }
}

bool DoorEntity::IsActive() const
{
    return isOpen;
}
