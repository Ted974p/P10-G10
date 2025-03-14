#include "PlatformEntity.h"

#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"

#include <iostream>

void PlatformEntity::onInitialize()
{
    addCollider(new RectangleCollider(this, sf::Vector2f(400, 400), sf::Vector2f(100, 100)));
    setRigidBody(true);
    setKinetic(false);
}
