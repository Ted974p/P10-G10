#include "LightEntity.h"

#include "../Entities/PlayerEntity.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"

#include <iostream>

#define COLUMNS 3
#define ROWS 1

void LightEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
    setRigidBody(false);
    setKinetic(false);

    sf::Texture* texture1 = resourceManager->GetTexture("props");
    if (!texture1) {
        std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
    }
    mSpriteSheet = new SpriteSheet(texture1, 4, 6);
    mSpriteSheet->setPosition(32, 32);
    mSpriteSheet->setScale(0.64f, 0.64f);
    mSpriteSheet->setCurrent(11);
}

void LightEntity::onCollision(Entity* other)
{
    if (other->isTag((int)Entity::TAG::Player))
    {
        PlayerEntity* player = dynamic_cast<PlayerEntity*>(other);
        if (player)
        {
            player->setInLightEntity(true);
            std::cout << "Entrée dans la lumière, boost activé !" << std::endl;
        }
    }
}


