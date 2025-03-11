#pragma once
#include "Entity.h"

class Player : public Entity
{

    sf::Vector2f mPosition;
    float mGravitySpeed = 8.2f;
protected:
    bool fall = false;
public:
    float mGravityAcceleration = 8.81f; 
    void MoveRight(float deltatime);
    void MoveLeft(float deltaTime);
    void Fall(float deltaTime);
    void SwitchFall();
};
