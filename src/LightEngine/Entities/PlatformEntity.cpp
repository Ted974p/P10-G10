#include "PlatformEntity.h"

#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"

#include <iostream>

void PlatformEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(1280, 100)));
    setRigidBody(true);
    setKinetic(false);
}
