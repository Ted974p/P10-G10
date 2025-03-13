#include "Player.h"
#include <iostream>

void Player::OnInitialize()
{
    SetEntityAffect(true);
    SetFalling(true);
}

void Player::MoveRight(float deltaTime)
{
    mSpeed += mAcceleration * deltaTime;
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    SetDirection(mSpeed,0,mSpeed);
}

void Player::MoveLeft(float deltaTime)
{
    mSpeed += mAcceleration * deltaTime;
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    SetDirection(-mSpeed, 0, -mSpeed);
}

void Player::Decelerate(float deltaTime)
{
    if (mSpeed > 0)
    {
        SetSpeed(mSpeed - mDeceleration * deltaTime);
        if (mSpeed < 0)
            SetSpeed(0);
    }
    std::cout << mSpeed << std::endl;
}