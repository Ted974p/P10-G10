#pragma once
#include "../Entity.h"
#include "../Interfaces/IActivable.h"

class DoorEntity : public Entity, public IActivable
{
private:
    bool isOpen = false;

public:
    virtual void onInitialize() override;
    virtual void Activate() override;
    virtual void Deactivate() override;
    virtual bool IsActive() const override;
};
