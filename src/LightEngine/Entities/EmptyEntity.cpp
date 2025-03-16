#include "EmptyEntity.h"
#include "../CircleCollider.h"

void EmptyEntity::onInitialize()
{
	setRigidBody(false);
	setKinetic(false);
}

void EmptyEntity::set(int x, int y)
{
	setPosition(x, y);
	setCollider(new CircleCollider(this,sf::Vector2f(0,0),10));
}


