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
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(1000, 1000)));
    setRigidBody(false);
    setKinetic(false);

    sf::Texture* texture4 = resourceManager->GetTexture("FX");
    if (!texture4) {
        std::cerr << "Erreur : Impossible de charger la texture 'FX'." << std::endl;
    }

    mSpriteSheet3 = new SpriteSheet(texture4, COLUMNS, ROWS);
    mSpriteSheet3->setPosition(50, 50);
}

