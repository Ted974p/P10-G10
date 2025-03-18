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

void LiftableEntity::onDownCollision(Entity* _other)
{
	if (!_other->isRigidBody())
		return;


	mIsGrounded = true;
}

void LiftableEntity::onColliding(Entity* _other)
{
	std::cout << "dffgdbfdbgfd" << std::endl;
	if (_other->isTag((int)Entity::TAG::Player))
	{
		setPlayerLifting(dynamic_cast<PlayerEntity*>(_other));
		mPlayerLifting->setLiftedObject(this);
	}
}

void LiftableEntity::onUpdate()
{
	if (mPlayerLifting != nullptr)
	{
		setPosition(mPlayerLifting->getPosition().x, mPlayerLifting->getPosition().y - 100);
	}



	//checkIfGrounded();
}

//void LiftableEntity::checkIfGrounded()
//{
//	sf::Vector2f pos = getPosition();
//	sf::Vector2f size = mColliderCast->getSize();
//
//	mGroundCheck->setPosition(pos + sf::Vector2f(0, size.y + 5));
//
//	for (Entity* entity : gameManager->getEntities())
//	{
//		if (entity == this) continue;
//
//		if (mGroundCheck->isColliding(entity->getCollider()))
//		{
//			mIsGrounded = true;
//			return;
//		}
//	}
//
//	mIsGrounded = false;
//}