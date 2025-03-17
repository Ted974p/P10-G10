#include "PlayerEntity.h"

#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include "../Scenes/AnimationScene.h"

#include <iostream>

#define COLUMNS 6
#define ROWS 8

void PlayerEntity::jump()
{
	if (mIsGrounded) {

		addForce(sf::Vector2f(0, -mJumpForce));
		mIsGrounded = false;
		if (isMovingLeft)
		{
			mAnimator->Play("jump_left_up");
		}
		else if (isMovingRight)
		{
			mAnimator->Play("jump_right_up");
		}
	}
}

void PlayerEntity::onDownCollision()
{
	std::cout << "Player touched the ground!" << std::endl;
	mForce.y = 0;
	mIsGrounded = true;
	isJumping = false;
}

void PlayerEntity::onInitialize()
{
	Timer = new sf::Clock();
	Timer->restart();
	isMovingLeft = false;
	isMovingRight = true;
	mSpeed = 0;
	mAcceleration = 45.f;
	mMaxSpeed = 180.f;
	mDeceleration = 50.f;
	mMass = 3;
	

	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(true);
	setKinetic(true);

	sf::Texture* texture = resourceManager->GetTexture("SpriteSheet1.2");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}

	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(50, 50);

	mAnimator = new Animator(mSpriteSheet,
		{
			new Animation("idle_right", 0, 5, 1),
			new Animation("idle_left", 6, 11, 1),
			new Animation("idleAnnim_right", 12, 17, 2,false),
			new Animation("idleAnnim_left", 18, 23, 2,false),
			new Animation("jump_right_down", 24, 26, 3),
			new Animation("jump_right_up", 27, 29, 4,false),
			new Animation("jump_left_up", 30, 32, 4,false),
			new Animation("jump_left_down", 33, 35, 4),
			new Animation("run_right", 36, 41, 3),
			new Animation("run_left", 42, 47, 4),
		});

	mAnimator->Play("idle_right");
}

void PlayerEntity::MoveRight(float deltaTime)
{
	if (isMovingLeft)
		Decelerate(deltaTime);

	else
	{
		if (mSpeed > mMaxSpeed)
			Decelerate(deltaTime);

		else
			mSpeed += mAcceleration * deltaTime;
		isMovingLeft = false;
		isMovingRight = true;
		isruning = true;
		if (mIsGrounded)
		{
		//	mAnimator->Play("run_right");
		}
	}

}


void PlayerEntity::MoveLeft(float deltaTime)
{
	if (isMovingRight)
		Decelerate(deltaTime);

	else
	{
		if (mSpeed < -mMaxSpeed)
			Decelerate(deltaTime);

		else
			mSpeed -= mAcceleration * deltaTime;

		isMovingRight = false;
		isMovingLeft = true;
		isruning = true;
		if (mIsGrounded)
		{
			//mAnimator->Play("run_left");
		}
	}
}

void PlayerEntity::Decelerate(float deltaTime)
{

	if (mSpeed > 100 || mSpeed < -100)
		mDeceleration = 70.f;
	else
		mDeceleration = 50.f;

	if (mSpeed > 1)
	{
		setSpeed(mSpeed - mDeceleration * deltaTime);
	}
	
	else if (mSpeed < -1)
    {
		setSpeed(mSpeed + mDeceleration * deltaTime);

    }

	else
	{
        setSpeed(0.f);
		isMovingRight = false;
		isMovingLeft = false;
		isruning = false;
	}
    
}




void PlayerEntity::onUpdate()
{
	if (inputManager->GetKeyDown("Jump"))
		jump();

	if (inputManager->GetAxis("Trigger") < 0)
		mMaxSpeed = 180.f;
	else
		mMaxSpeed = 100.f;

	float horizontal = inputManager->GetAxis("Horizontal");
	AnimationScene* aScene = getScene<AnimationScene>();
	float dt = aScene->getDeltaTime();
	if (horizontal == 1)
	{
		MoveRight(dt);
	}
	else if (horizontal == -1)
	{
		MoveLeft(dt);
	}
	else
	{
		Decelerate(dt);
	}
	std::cout << mSpeed << std::endl;
	if (mSpeed < -1 || mSpeed > 1)
	{
		move(mSpeed * getDeltaTime(), 0);
	}
	/*if (mIsGrounded)
	{
		if (isruning)
		{

		}
		else if (Timer->getElapsedTime().asSeconds() >= 5)
		{
			std::cout << "test";

			if (isMovingLeft)
			{
				mAnimator->Play("idleAnnim_left");
			}
			else if (isMovingRight)
			{
				mAnimator->Play("idleAnnim_right");
			}
			else
			{
				mAnimator->Play("idleAnnim_right");
			}
			Timer->restart();

		}

		else
		{
			if (isMovingLeft)
			{
				mAnimator->Play("idle_left");
			}
			else if (isMovingRight)
			{
				mAnimator->Play("idle_right");
			}
		}
	}
	*/
}
