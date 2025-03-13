#pragma once
#include "Entity.h"

class Player : public Entity
{

public:
    void OnInitialize() override;
    void MoveRight(float deltatime);
    void MoveLeft(float deltaTime);
    void Decelerate(float deltatime);
};
