#include "Player.h"
#include <iostream>

void Player::MoveRight(float deltaTime)
{
    mSpeed += mAcceleration * deltaTime;
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    SetPosition(GetPosition().x + mSpeed, GetPosition().y);
    std::cout << GetPosition().x << "  " << GetPosition().y << std::endl;
}

void Player::MoveLeft(float deltaTime)
{
    mSpeed += mAcceleration * deltaTime;
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    SetPosition(GetPosition().x - mSpeed, GetPosition().y);
    std::cout << GetPosition().x << "  " << GetPosition().y << std::endl;
}
