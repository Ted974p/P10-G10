#include "LightEntity2.h"

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

void LightEntity2::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(1000, 1500)));
    setRigidBody(false);
    setKinetic(false);

    sf::Texture* texture4 = resourceManager->GetTexture("FX2");
    if (!texture4) {
        std::cerr << "Erreur : Impossible de charger la texture 'FX'." << std::endl;
    }

    mSpriteSheet = new SpriteSheet(texture4, COLUMNS, ROWS);
    mSpriteSheet->setPosition(250, 320);
    mSpriteSheet->setRotation(-30.f);
    mSpriteSheet->setScale(0.7f, 1.f);
    mSpriteSheet->setColor(sf::Color(255, 255, 255, 128));
}

void LightEntity2::onUpdate()
{
}

