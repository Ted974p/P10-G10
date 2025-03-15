#pragma once
#include "../Entity.h"

class Animator;

class DoorEntity : public Entity
{
private:
    Animator* animator;  

public:
    void onInitialize() override;
};
