#include "TargetEntity.h"
#include "../RectangleCollider.h"

void TargetEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
	setRigidBody(false);
	setKinetic(false);
}
