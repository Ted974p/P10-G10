#include "ButtonEntity.h"
#include "../Interfaces/IActivable.h"

#include "../Managers/GameManager.h"
#include "../Managers/ResourceManager.h"

#include "../Rendering/SpriteSheet.h"

#include "../RectangleCollider.h"

void ButtonEntity::onInitialize()
{
    closingStarted = false;

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
    mSpriteSheet->setCurrent(13);

    // filoutage pour camoufler les problèmes de spritesheet
    sf::Vector2f hv = mSpriteSheet->getHV();
    sf::Vector2f xy = mSpriteSheet->getXY();
    mSpriteSheet->setTextureRect(sf::IntRect(xy.x * hv.x, xy.y * hv.y + 2, hv.x, hv.y));
}

void ButtonEntity::AddActivableEntity(IActivable* activable)
{
    if (activable)
        activableEntities.push_back(activable);
}

void ButtonEntity::onCollisionEnter(Entity* other)
{
    if (!other->isTag(TAG::Player))
        return;

    mSpriteSheet->setCurrent(12);

    if (!closingStarted && !activableEntities.empty())
    {
        for (IActivable* entity : activableEntities)
        {
            if (entity)
                entity->Activate();
        }

        closingTimer.restart();
        closingStarted = true;
    }
}

void ButtonEntity::onCollisionExit(Entity* other)
{
    mSpriteSheet->setCurrent(13);
}

void ButtonEntity::onUpdate()
{
    if (closingStarted && closingTimer.getElapsedTime().asSeconds() >= activationDuration)
    {
        for (IActivable* entity : activableEntities)
        {
            if (entity)
                entity->Deactivate();
        }

        closingStarted = false;
    }
}
