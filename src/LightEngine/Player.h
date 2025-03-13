#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"

class Player : public Entity
{   
    sf::Vector2f mPosition;
    sf::Sprite sprite;

public:

    void OnInitialize() override;
    bool isMoving = false;
    void MoveRight(float deltatime);
    void MoveLeft(float deltaTime);
    void Decelerate(float deltatime);
    void OnInitialize() override;
    void OnUpdate() override;
    void Jump();
};
