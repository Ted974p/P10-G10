#include "Player.h"
#include <iostream>

void Player::MoveRight(float deltaTime)
{
    mSpeed += mAcceleration ;
    mPosition = GetPosition();
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    mPosition.x +=  30.f ;
    GoToPosition(mPosition.x,mPosition.y,mSpeed);
}
void Player::MoveLeft(float deltaTime)
{
    mSpeed += mAcceleration ;
    mPosition = GetPosition();
    if (mSpeed > mMaxSpeed)
        mSpeed = mMaxSpeed;
    mPosition.x -=  30.f;
    GoToPosition(mPosition.x, mPosition.y,mSpeed);
}
void Player::Fall(float deltaTime)
{
    if (fall == false)
    {
        return;
    }
    else
    {
        float Height = GetScene()->GetWindowHeight();
        mPosition = GetPosition();
        mPosition.y = Height;
        float mMaxGravitySpeed = mGravitySpeed * mGravityAcceleration;
        GoToDirection(mPosition.x, mPosition.y, mMaxGravitySpeed);
    }
}

void Player::SwitchFall()
{
    if (fall == false)
    {
        fall = true;
        return;
    }
    else if (fall == true)
    {
        fall = false;
       
    }
}
