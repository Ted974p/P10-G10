#include "Player.h"
#include <iostream>

void Player::MoveRight(float deltaTime)
{
    mSpeed += mAcceleration * deltaTime;
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    mPosition.x += mSpeed * deltaTime;
    SetPosition(mPosition.x, mPosition.y);
}

void Player::MoveLeft(float deltaTime)
{
    mSpeed += mAcceleration * deltaTime;
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    mPosition.x -= mSpeed * deltaTime;
    SetPosition(mPosition.x, mPosition.y);
}
