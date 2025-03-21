#pragma once
#include "../Entity.h"
#include "../RectangleCollider.h"

class MovingPlatform : public Entity
{
protected:

    bool isActive = false;
    sf::Clock movingTimer;
    bool movingStarted = false;

    sf::Vector2f startPosition;
    sf::Vector2f direction;
    int maxDistance;
    bool loopMovement = true;
    bool mHasReturnedToStart = false; 
    bool mIsStopped = false;

public:
    virtual void onInitialize() override;
    virtual void onUpdate() override;

    void setDirection(float x, float y) { direction = sf::Vector2f(x, y); }
    void setDistance(int distance) { maxDistance = distance; }
    void setLoop(bool loop) { loopMovement = loop; }
    void setActive(bool _active) { isActive = _active; }
};
