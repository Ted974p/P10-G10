#include "Entity.h"

#include "Utils/Utils.h"
#include "Utils/Debug.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Collider.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"

#include "Managers/GameManager.h"
#include "Rendering/SpriteSheet.h"
#include "Rendering/Animator.h"

#include "Entities/ButtonEntity.h"
#include "Entities/PlayerEntity.h"

#include <iostream>

const float POSITION_TOLERANCE = 2.0f;

//
// ==================== INITIALISATION & DESTRUCTION ====================
//

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

    onDestroy();
}

//
// ==================== PHYSIQUE & DÉPLACEMENT ====================
//

bool Entity::goToDirection(int x, int y, float speed)
{
    sf::Vector2f position = getPosition();
    sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);

    if (!Utils::Normalize(direction))
        return false;

    setDirection(direction.x, direction.y, speed);
    return true;
}

bool Entity::goToPosition(int x, int y, float speed)
{
    sf::Vector2f position = getPosition();
    float distance = Utils::GetDistance(position.x, position.y, x, y);

    if (distance <= POSITION_TOLERANCE)
    {
        setPosition(sf::Vector2f(x, y));
        mTarget.isSet = false;
        return true;
    }

    if (!goToDirection(x, y, speed))
        return false;

    mTarget.position = { x, y };
    mTarget.distance = distance;
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

//
// ==================== COLLISIONS ====================
//

bool Entity::detectCollision(Entity* _other)
{
    Collider* otherCollider = _other->getCollider();
    bool collisionDetected = mCollider->isColliding(otherCollider);

    if (collisionDetected)
    {
        if (!mIsColliding[_other])
        {
            mIsColliding[_other] = true;
            mIsEnter = true;
            mIsExit = false;

            onCollisionEnter(_other);
            _other->onCollisionEnter(this);
        }
        else
        {
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
        case 1: onUpCollisionEnter(other); other->onDownCollisionEnter(this); break;
        case 2: onRightCollisionEnter(other); other->onLeftCollisionEnter(this); break;
        case 3: onLeftCollisionEnter(other); other->onRightCollisionEnter(this); break;
        case 4: onDownCollisionEnter(other); other->onUpCollisionEnter(this); break;
        }
    }
    else if (mIsExit && other->mIsExit)
    {
        switch (collisionSide)
        {
        case 1: onUpCollisionExit(other); other->onDownCollisionExit(this); break;
        case 2: onRightCollisionExit(other); other->onLeftCollisionExit(this); break;
        case 3: onLeftCollisionExit(other); other->onRightCollisionExit(this); break;
        case 4: onDownCollisionExit(other); other->onUpCollisionExit(this); break;
        }
    }
    else
    {
        switch (collisionSide)
        {
        case 1: onUpCollision(other); other->onDownCollision(this); break;
        case 2: onRightCollision(other); other->onLeftCollision(this); break;
        case 3: onLeftCollision(other); other->onRightCollision(this); break;
        case 4: onDownCollision(other); other->onUpCollision(this); break;
        }
    }
}

//
// ==================== MISE À JOUR ====================
//

void Entity::update()
{
    if (mAnimator != nullptr && mSpriteSheet != nullptr)
    {
        mAnimator->Update(getDeltaTime());
    }

    onUpdate();
}

//
// ==================== RENDU ====================
//

void Entity::showGizmos()
{
    mCollider->showGizmos();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.combine(getTransform());

    if (mSpriteSheet) {
        target.draw(*mSpriteSheet, states);
    }
    if (mSpriteSheet2) {
        target.draw(*mSpriteSheet2, states);
    }
}

//
// ==================== ACCÈS AUX DONNÉES ====================
//

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
