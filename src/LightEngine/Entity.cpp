#include "Entity.h"

#include "Utils/Utils.h"
#include "Utils/Debug.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Collider.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include <iostream>

#include "Managers/GameManager.h"
#include "Rendering/SpriteSheet.h"
#include "Rendering/Animator.h"

void Entity::initialize()
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	
	mTarget.isSet = false;

	onInitialize();
}

bool Entity::processCollision(Entity* other) const
{
	bool isColliding = false;
	for (Collider* colliderThis : mColliders) 
	{
		for (Collider* colliderOther : other->getColliders()) 
		{
			if (!colliderThis->isColliding(colliderOther)) 
				continue;

			isColliding = true;
			colliderThis->onColliding();

			if (!isRigidBody() || !other->isRigidBody())
				continue;

			colliderThis->repulse(colliderOther);
		}
	}
	return isColliding;
}

void Entity::destroy()
{
	mToDestroy = true;

	for (Collider* collider : mColliders)
		delete collider;
	mColliders.clear();

	delete mSpriteSheet;

	onDestroy();
}

bool Entity::goToDirection(int x, int y, float speed)
{
	sf::Vector2f position = getPosition();
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	setDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::goToPosition(int x, int y, float speed)
{
	if (goToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = getPosition();

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::setDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

void Entity::Falling(int DeltaTime)
{
	if (mFalling == false)
	{
		return;
	}
	mGravitySpeed += mGravityAcceleration * DeltaTime;
	if (mGravitySpeed > mMaxGravitySpeed)
		mGravitySpeed = mMaxGravitySpeed;


}

void Entity::update()
{
	float dt = getDeltaTime();


	if (mAnimator != nullptr && mSpriteSheet != nullptr)
	{
		mAnimator->Update(dt);
	}

	if (mAffect == true)
	{
		Falling(dt);
	}

	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	move(translation);

	if (mTarget.isSet) 
	{
		float x1 = getPosition().x;
		float y1 = getPosition().y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			setPosition(mTarget.position.x, mTarget.position.y);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	onUpdate();
}

Scene* Entity::getScene() const
{
	return gameManager->GetScene();
}

float Entity::getDeltaTime() const
{
	return gameManager->GetDeltaTime();
}

void Entity::addCollider(CircleCollider* _collider)
{
	mColliders.push_back(_collider);
}

void Entity::addCollider(RectangleCollider* _collider)
{
	mColliders.push_back(_collider);
}

void Entity::showGizmos()
{
	for (Collider* collider : mColliders)
		collider->showGizmos();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.combine(getTransform());

	if (mSpriteSheet) {
		target.draw(*mSpriteSheet, states);
	}
}

