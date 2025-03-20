#pragma once
#include "../Entity.h"

class IActivable;

class ButtonEntity : public Entity
{
private:
    IActivable* activableEntity;
    sf::Clock closingTimer;
    bool closingStarted = false;
    const float ACTIVATION_DURATION = 5.0f;

public:
    virtual void onInitialize() override;
    void SetActivableEntity(IActivable* activable);
    virtual void onCollision(Entity* other) override;
    virtual void onUpdate() override;
};
