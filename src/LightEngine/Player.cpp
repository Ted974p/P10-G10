
//#include "Player.h"
//#include <iostream>
//#include "SceneMS.h"
//
////void Player::MoveRight(float deltaTime)
////{
////
////    mSpeed += mAcceleration * deltaTime;
////    if (mSpeed > mMaxSpeed)
////        mSpeed = mMaxSpeed;
////
////    SetPosition(GetPosition().x + mSpeed, GetPosition().y);
////}
//
//void Player::MoveRight(float deltaTime)
//{
//
//    mSpeed += mAcceleration * deltaTime;
//    if (mSpeed > mMaxSpeed)
//        mSpeed = mMaxSpeed;
//
//    setDirection(mSpeed, 0, mSpeed);
//    isMoving = true;
//}
//
////void Player::MoveLeft(float deltaTime)
////{
////    
////    mSpeed += mAcceleration * deltaTime;
////    if (mSpeed > mMaxSpeed)
////        mSpeed = mMaxSpeed;
////    
////
////    SetPosition(GetPosition().x - mSpeed, GetPosition().y);
////    std::cout << mDirection.x << std::endl;
////}
//
//void Player::MoveLeft(float deltaTime)
//{
//
//    mSpeed += mAcceleration * deltaTime;
//    if (mSpeed > mMaxSpeed)
//        mSpeed = mMaxSpeed;
//
//    setDirection(-mSpeed, 0, -mSpeed);
//    isMoving = true;
//}
//
//void Player::Decelerate(float deltaTime)
//{
//    if (mSpeed > 0)
//    {
//        setSpeed(mSpeed - mDeceleration * deltaTime);
//        if (mSpeed < 0)
//        {
//            setSpeed(0);
//            isMoving = false;
//        }
//    }
//}
//
//void Player::Fall(float deltaTime)
//{
//    if (isFalling == false)
//    {
//        return;
//    }
//    else
//    {
//        float Height = getScene()->GetWindowHeight();
//        mPosition = getPosition();
//        mPosition.y = Height;
//        float mMaxGravitySpeed = mGravitySpeed * mGravityAcceleration;
//        goToDirection(mPosition.x, mPosition.y, mMaxGravitySpeed);
//    }
//}
//
//void Player::SwitchFall()
//{
//    if (isFalling == false)
//    {
//        isFalling = true;
//        return;
//    }
//    else if (isFalling == true)
//    {
//        isFalling = false;
//
//    }
//}
//
//void Player::OnInitialize()
//{
//    sf::Texture texture;
//    if (!texture.loadFromFile("./image/image_pixel.PNG"))
//    {
//        // error...
//    }
//    sprite.setTexture(texture);
//}
//
//void Player::OnUpdate()
//{
//    SceneMS* scene = (SceneMS*)getScene();
//
//    //  scene.
//}
//
//void Player::Jump()
//{
//    //SetImpulsion(500.f);
//}
