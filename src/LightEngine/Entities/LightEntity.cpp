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

#define COLUMNS 3
#define ROWS 1

void LightEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    setRigidBody(false);
    setKinetic(false);

    //sf::Texture* texture4 = resourceManager->GetTexture("FX");

    //mSpriteSheet3 = new SpriteSheet(texture4, COLUMNS, ROWS);
    //mSpriteSheet3->setPosition(50, 50);

    //mAnimator3 = new Animator(mSpriteSheet2,
    //    {
    //    new Animation("idle", 0, 6, 3),
    //        new Animation("Light", 1, 6,2),
    //    });
    //mAnimator3->Play("Light");
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


