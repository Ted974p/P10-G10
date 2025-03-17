
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

#include "Entities/PlayerEntity.h"

void Entity::initialize()
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	mTarget.isSet = false;

	onInitialize();
}

bool Entity::processCollision(Entity* _other)
{
	Collider* otherCollider = _other->getCollider();

	int isColliding = mCollider->isColliding(otherCollider);

	if (dynamic_cast<PlayerEntity*>(this) != nullptr)
		std::cout << isColliding << std::endl;

	if (!isColliding)
		return false;

	onColliding(_other);

	if (mCollider->getShapeTag() == ShapeTag::Rectangle && otherCollider->getShapeTag() == ShapeTag::Rectangle)
	{
		switch (isColliding)
		{
		case 1:
			onUpCollision(_other);
			break;
		case 2:
			onRightCollision(_other);
			break;
		case 3:
			onLeftCollision(_other);
			break;
		case 4:
			onDownCollision(_other);
			break;
		}
	}

	if (!isRigidBody() || !_other->isRigidBody())
		return true;

	mCollider->repulse(otherCollider);

	return true;
}

void Entity::destroy()
{
	mToDestroy = true;

	delete mCollider;

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

void Entity::applyGravity(float _dt)
{
	if (!mIsKinetic)
		return;

	if (mIsGrounded)
		return;

	mForce += sf::Vector2f(0, mGravityForce * mMass * _dt);
}

void Entity::update()
{
	onUpdate();

	float dt = getDeltaTime();

	if (mAnimator != nullptr && mSpriteSheet != nullptr)
	{
		mAnimator->Update(dt);
	}

	applyGravity(dt);

	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;

	move(translation);
	move(mForce);

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
}

Scene* Entity::getScene() const
{
	return gameManager->GetScene();
}

float Entity::getDeltaTime() const
{
	return gameManager->GetDeltaTime();
}

void Entity::setCollider(CircleCollider* _collider)
{
	mCollider = _collider;
}

void Entity::setCollider(RectangleCollider* _collider)
{
	mCollider = _collider;
}

void Entity::showGizmos()
{
	mCollider->showGizmos();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.combine(getTransform());

	if (mSpriteSheet) {
		target.draw(*mSpriteSheet, states);
	}
}
