#pragma once
#include "PlatformEntity.h"
#include "../RectangleCollider.h"

class TargetEntity;

class MovingPlatform : public PlatformEntity
{
private:
    sf::Clock movingTimer;
    bool movingStarted = false;
    const float MOVING_DELAY = 4.0f;
    sf::Vector2f originalPosition;
    TargetEntity* targetEntity = nullptr;
    bool movingTowardsTarget = true;

public:
    virtual void onInitialize() override;
    virtual void onUpdate() override;
    virtual void onCollision(Entity* other) override;

    void setTargetEntity(TargetEntity* target) { targetEntity = target; }
};
