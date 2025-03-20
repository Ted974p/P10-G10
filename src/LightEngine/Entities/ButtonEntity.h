#pragma once
#include "../Entity.h"
#include <vector>

class IActivable;

class ButtonEntity : public Entity
{
private:
    std::vector<IActivable*> activableEntities;
    sf::Clock closingTimer;
    bool closingStarted = false;
    float activationDuration = 5.0f;

public:
    virtual void onInitialize() override;
    void AddActivableEntity(IActivable* activable);
    virtual void onCollisionEnter(Entity* other) override;
    virtual void onCollisionExit(Entity* other) override;
    virtual void onUpdate() override;
    virtual void setActivationDuration(float _activationDuration) { activationDuration = _activationDuration; };
};
