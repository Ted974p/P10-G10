
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

#include "Entities/ButtonEntity.h"
#include "Entities/PlayerEntity.h"


void Entity::initialize()
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	mTarget.isSet = false;

	onInitialize();
}

bool Entity::detectCollision(Entity* _other)
{
    Collider* otherCollider = _other->getCollider();
    bool collisionDetected = mCollider->isColliding(otherCollider);

    if (collisionDetected)
    {
        if (!mIsColliding[_other])
        {
            // Nouvelle collision : on active le flag d'entr�e pour cette frame
            mIsColliding[_other] = true;
            mIsEnter = true;
            mIsExit = false;

            onCollisionEnter(_other);
            _other->onCollisionEnter(this);
        }
        else
        {
            // Collision continue : on r�initialise le flag d'entr�e (il ne doit �tre vrai que lors de la premi�re frame de collision)
            mIsEnter = false;
            onCollision(_other);
            _other->onCollision(this);
        }
        return true;
    }
    else
    {
        if (mIsColliding[_other])
        {
            // Si la collision existait et qu'elle n'est plus d�tect�e, on active le flag de sortie
            mIsColliding[_other] = false;
            mIsExit = true;
            mIsEnter = false;
            onCollisionExit(_other);
            _other->onCollisionExit(this);
        }
        else
        {
            mIsExit = false;
            mIsEnter = false;
        }
        return false;
    }
}


void Entity::applyRepulsion(Entity* other)
{
    if (isRigidBody() && other->isRigidBody())
    {
        mCollider->repulse(other->getCollider());
    }
}

void Entity::applySideCollisions(Entity* other)
{
    int collisionSide = mCollider->getCollisionSide(other->getCollider());
    mIsGrounded = false;

    if (collisionSide == 0)
        return;

    if (mIsEnter && other->mIsEnter)
    {
        switch (collisionSide)
        {
        case 1:
            onUpCollisionEnter(other);
            other->onDownCollisionEnter(this);
            break;
        case 2:
            onRightCollisionEnter(other);
            other->onLeftCollisionEnter(this);
            break;
        case 3:
            onLeftCollisionEnter(other);
            other->onRightCollisionEnter(this);
            break;
        case 4:
            onDownCollisionEnter(other);
            other->onUpCollisionEnter(this);
            break;
        }
    }
    else if (mIsExit && other->mIsExit)
    {
        switch (collisionSide)
        {
        case 1:
            onUpCollisionExit(other);
            other->onDownCollisionExit(this);
            break;
        case 2:
            onRightCollisionExit(other);
            other->onLeftCollisionExit(this);
            break;
        case 3:
            onLeftCollisionExit(other);
            other->onRightCollisionExit(this);
            break;
        case 4:
            onDownCollisionExit(other);
            other->onUpCollisionExit(this);
            break;
        }
    }
    else
    {
        // Collision continue
        switch (collisionSide)
        {
        case 1:
            onUpCollision(other);
            other->onDownCollision(this);
            break;
        case 2:
            onRightCollision(other);
            other->onLeftCollision(this);
            break;
        case 3:
            onLeftCollision(other);
            other->onRightCollision(this);
            break;
        case 4:
            onDownCollision(other);
            other->onUpCollision(this);
            break;
        }
    }
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

    //std::cout << mIsGrounded << std::endl;

    if (mIsGrounded)
        mForce.y += mGravityForce * mMass * _dt;
    else
        mForce += sf::Vector2f(0, mGravityForce * mMass * _dt);
}

void Entity::updatePhysics(float deltaTime)
{
    applyGravity(getDeltaTime());

    float distance = deltaTime * mSpeed;

    sf::Vector2f translation = mDirection * distance;

    move(translation);

    move(mForce * deltaTime);
}

void Entity::update()
{
    if (mAnimator != nullptr && mSpriteSheet != nullptr)
    {
        mAnimator->Update(getDeltaTime());
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
