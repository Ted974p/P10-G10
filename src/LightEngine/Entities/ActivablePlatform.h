#pragma once
#include "MovingPlatform.h"
#include "../Interfaces/IActivable.h"

class ActivablePlatform : public MovingPlatform, public IActivable
{
public:
    void Activate() override {
        isActive = true;
        mIsStopped = false;
    }

    void Deactivate() override {
        isActive = false;
        mIsStopped = true; 
    }

    bool IsActive() const override {
        return isActive;
    }
};
