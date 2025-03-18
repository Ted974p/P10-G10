#include "ObstacleEntity.h"
#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include <iostream>

void ObstacleEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 200)));
	setRigidBody(true);
	setKinetic(true);

	mColliderCast = dynamic_cast<RectangleCollider*>(getCollider());

	sf::Vector2f pos = getPosition();
	sf::Vector2f size = mColliderCast->getSize();
	mGroundCheck = new RectangleCollider(this, pos + sf::Vector2f(0, size.y + 5), sf::Vector2f(size.x, 5));


	setTag(int(Entity::TAG::Obstacle));
}

void ObstacleEntity::onDownCollision(Entity* other)
{
	if (!other->isRigidBody())
		return;

	if (mForce.y < 0)
		return;

	mForce.y = 0;
	mIsGrounded = true;
}

void ObstacleEntity::checkIfGrounded()
{
	sf::Vector2f pos = getPosition();
	sf::Vector2f size = mColliderCast->getSize();



	mGroundCheck->setPosition(pos + sf::Vector2f(0, size.y + 5));

	for (Entity* entity : gameManager->getEntities())
	{
		if (entity == this) continue;

		if (mGroundCheck->isColliding(entity->getCollider()))
		{
			mIsGrounded = true;
			return;
		}
	}

	mIsGrounded = false;
}

void ObstacleEntity::onUpdate()
{
	checkIfGrounded();
}
