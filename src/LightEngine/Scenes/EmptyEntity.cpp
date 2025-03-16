#include "EmptyEntity.h"
#include "../RectangleCollider.h"
void EmptyEntity::onInitialize()
{
	setRigidBody(false);
	setKinetic(false);
}

void EmptyEntity::Set(int x, int y)
{
	setPosition(x, y);
	setCollider(new RectangleCollider(this, sf::Vector2f(x, y), sf::Vector2f(100, 100)));
}

