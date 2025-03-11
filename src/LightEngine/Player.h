#pragma once
#include "Entity.h"

class Player : public Entity
{

public:
    void MoveRight(float deltatime);
    void MoveLeft(float deltaTime);
};
