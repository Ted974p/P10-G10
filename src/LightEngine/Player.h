#pragma once
#include "Entity.h"

class Player : public Entity
{
    sf::Vector2i mPosition;

public:
    void MoveRight(float deltatime);
    void MoveLeft(float deltaTime);
};
