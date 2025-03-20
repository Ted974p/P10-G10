#include "ButtonEntity.h"
#include "../Interfaces/IActivable.h"
#include "../Managers/GameManager.h"

void ButtonEntity::onInitialize()
{
    activableEntity = nullptr;
}

void ButtonEntity::SetActivableEntity(IActivable* activable)
{
    activableEntity = activable;
}

void ButtonEntity::onCollision(Entity* other)
{
    if (activableEntity && !closingStarted)
    {
        activableEntity->Activate();  // Active l'entité associée
        closingTimer.restart();
        closingStarted = true;
    }
}

void ButtonEntity::onUpdate()
{
    if (closingStarted && closingTimer.getElapsedTime().asSeconds() >= ACTIVATION_DURATION)
    {
        if (activableEntity)
            activableEntity->Deactivate();  // Désactive après le délai

        closingStarted = false;
    }
}
