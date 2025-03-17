#include "LightEntity.h"

#include "../Entities/PlayerEntity.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include "../Scenes/AnimationScene.h"

#include <iostream>

void LightEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    setRigidBody(false);
    setKinetic(false);
}

void LightEntity::onColliding(Entity* other)
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


