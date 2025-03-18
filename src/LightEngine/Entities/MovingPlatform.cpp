#include "MovingPlatform.h"
#include <iostream>

void MovingPlatform::onInitialize()
{
	setDirection(1, 0);
	setSpeed(30);

	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(200, 50)));


	setTag(int(Entity::TAG::MovingPlatform));
	setRigidBody(true);
}



void MovingPlatform::onUpdate()
{

	if (movingTimer.getElapsedTime().asSeconds() >= MOVING_DELAY) {
		mDirection.x *= -1; 
		movingTimer.restart();
	}

	move(mDirection * mSpeed * getDeltaTime());
}

void MovingPlatform::onCollision(Entity* _other)
{
	if (_other->isTag((int)Entity::TAG::Plateform))
	{
		mDirection.x *= -1;
		movingTimer.restart();
	}
}
