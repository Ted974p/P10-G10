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

// --------------------------------------------------------
// Initialisation et destruction
// --------------------------------------------------------

void Entity::initialize()
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mTarget.isSet = false;

	onInitialize();
}

void Entity::destroy()
{
	mToDestroy = true;

	delete mCollider;
	delete mSpriteSheet;

	removeAllChildren();

	onDestroy();
}

// --------------------------------------------------------
// Gestion des collisions
// --------------------------------------------------------

bool Entity::processCollision(Entity* other)
{
	Collider* otherCollider = other->getCollider();

	int isColliding = mCollider->isColliding(otherCollider);
	if (!isColliding)
		return false;

	onColliding();

	if (!isRigidBody() || !other->isRigidBody())
		return true;

	mCollider->repulse(otherCollider);

	return true;
}

// --------------------------------------------------------
// Gestion de la position
// --------------------------------------------------------

bool Entity::goToDirection(int x, int y, float speed)
{
	sf::Vector2f position = getPosition();
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);

	bool success = Utils::Normalize(direction);
	if (!success)
		return false;

	setDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::goToPosition(int x, int y, float speed)
{
	if (!goToDirection(x, y, speed))
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
	if (!mIsKinetic || mIsGrounded)
		return;

	mForce += sf::Vector2f(0, mGravityForce * mMass * _dt);
}

void Entity::setRelativePosition(const sf::Vector2f& position)
{
	mLocalPosition = position;
	setPosition(mParent ? mParent->getPosition() + mLocalPosition : mLocalPosition);
}

void Entity::moveRelative(const sf::Vector2f& offset)
{
	mLocalPosition += offset;
	setPosition(getPosition() + mLocalPosition);
}

// --------------------------------------------------------
// Mise à jour de l'entité et des enfants
// --------------------------------------------------------

void Entity::update()
{
	onUpdate();

	if (mParent == nullptr)
	{
		float dt = getDeltaTime();
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
	else
	{
		setPosition(mParent->getPosition() + mLocalPosition);
	}

	updateChildrens();
}

void Entity::updateChildrens()
{
	for (Entity* child : mChildrens)
	{
		if (child)
		{
			child->setPosition(getPosition() + child->getLocalPosition());
		}
	}
}

// --------------------------------------------------------
// Gestion des enfants
// --------------------------------------------------------

void Entity::addChildren(Entity* child)
{
	if (!child || child == this) return; // Empêche l'ajout de soi-même

	if (child->mParent == this) return; // Si l'enfant est déjà ajouté

	if (child->mParent)
	{
		child->mParent->removeChild(child); // Retirer l'enfant de son parent précédent
	}

	mChildrens.push_back(child);
	child->mParent = this;
}

void Entity::removeChild(Entity* child)
{
	auto it = std::find(mChildrens.begin(), mChildrens.end(), child);
	if (it != mChildrens.end())
	{
		(*it)->mParent = nullptr;
		mChildrens.erase(it);
	}
}

void Entity::removeAllChildren()
{
	// Retirer tous les enfants et les détacher de ce parent
	for (Entity* child : mChildrens)
	{
		child->mParent = nullptr;
	}
	mChildrens.clear();
}

// --------------------------------------------------------
// Accesseurs et autres méthodes
// --------------------------------------------------------

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
	if (mCollider != nullptr) {
		mCollider->showGizmos();
	}
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());

	if (mSpriteSheet) {
		target.draw(*mSpriteSheet, states);
	}
}
