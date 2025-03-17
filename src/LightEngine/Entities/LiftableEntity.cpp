#include "LiftableEntity.h"
#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include <iostream>

void LiftableEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(true);
	setKinetic(true);
}

void LiftableEntity::onColliding(Entity* _other)
{
	if (_other->isTag((int)Entity::TAG::Player))
	{
		setPlayerLifting(dynamic_cast<PlayerEntity*>(_other));
		setKinetic(false);
	}
}

void LiftableEntity::onUpdate()
{
	if (mPlayerLifting != nullptr)
	{
		setPosition(mPlayerLifting->getPosition().x, mPlayerLifting->getPosition().y + 100);
	}
}

