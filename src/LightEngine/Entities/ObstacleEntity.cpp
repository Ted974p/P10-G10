#include "ObstacleEntity.h"
#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include <iostream>

void ObstacleEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(true);
	setKinetic(true);
}

void ObstacleEntity::onDownCollision(Entity* _other)
{
	mForce.y = 0;
	mIsGrounded = true;
}