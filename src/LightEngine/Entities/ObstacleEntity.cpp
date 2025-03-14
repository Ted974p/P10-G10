#include "ObstacleEntity.h"
#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include <iostream>

#define COLUMNS 6
#define ROWS 1

void ObstacleEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(false);
	setKinetic(true);
}
