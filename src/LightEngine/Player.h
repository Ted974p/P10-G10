#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"

class Player : public Entity
{
    
    sf::Vector2f mPosition;
    float mGravitySpeed = 8.2f;
    sf::Sprite sprite;
protected:
    bool fall = false;
public:
    float mGravityAcceleration = 8.81f; 
    void MoveRight(float deltatime);
    void MoveLeft(float deltaTime);
    void Fall(float deltaTime);
    void SwitchFall();
    void OnInitialize() override;
    void OnUpdate() override;
};
