#include "MovingPlatform.h"
#include "TargetEntity.h"

void MovingPlatform::onInitialize()
{
    setDirection(1, 0);
    setSpeed(30);
    originalPosition = getPosition();  // Store the initial position of the platform

    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(200, 50)));
    setTag(int(Entity::TAG::MovingPlatform));
    setRigidBody(true);
}

void MovingPlatform::onUpdate()
{
    if (targetEntity != nullptr)
    {
        sf::Vector2f targetPosition = targetEntity->getPosition();
        sf::Vector2f directionToTarget = targetPosition - getPosition();
        float distanceToTarget = std::sqrt(directionToTarget.x * directionToTarget.x + directionToTarget.y * directionToTarget.y);

        if (distanceToTarget > 1.0f)
        {
            directionToTarget /= distanceToTarget;
            move(directionToTarget * mSpeed * getDeltaTime());
        }
        else  // Reached the target
        {
            if (movingTowardsTarget)
            {
                movingTowardsTarget = false;
                movingTimer.restart();
            }
            else
            {
                sf::Vector2f directionBack = originalPosition - getPosition();
                float distanceBack = std::sqrt(directionBack.x * directionBack.x + directionBack.y * directionBack.y);
                if (distanceBack > 1.0f)
                {
                    directionBack /= distanceBack;
                    move(directionBack * mSpeed * getDeltaTime());
                }
            }
        }
    }

    if (movingTimer.getElapsedTime().asSeconds() >= MOVING_DELAY)
    {
        movingTimer.restart();
    }
}

void MovingPlatform::onCollision(Entity* _other)
{
    if (_other->isTag((int)Entity::TAG::Plateform))
    {
        mDirection.x *= -1;
        movingTimer.restart();
    }
}
