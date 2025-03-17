#pragma once
#include "../Entity.h"

class DoorEntity;

class ButtonEntity : public Entity
{
    DoorEntity* door;  

public:
    void setDoor(DoorEntity* doorEntity);
    virtual void onInitialize() override;
    void onColliding(Entity* other);
};
