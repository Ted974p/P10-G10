#include "Player.h"
#include <iostream>

void Player::onInitialize()
{
    SetEntityAffect(true);
    SetFalling(true);
}

void Player::MoveRight(float deltaTime)
{
    mSpeed += mAcceleration * deltaTime;
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    setDirection(mSpeed,0,mSpeed);
}

void Player::MoveLeft(float deltaTime)
{
    mSpeed += mAcceleration * deltaTime;
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    setDirection(-mSpeed, 0, -mSpeed);
}

void Player::Decelerate(float deltaTime)
{
    if (mSpeed > 0)
    {
        setSpeed(mSpeed - mDeceleration * deltaTime);
        if (mSpeed < 0)
            setSpeed(0);
    }
    std::cout << mSpeed << std::endl;
}