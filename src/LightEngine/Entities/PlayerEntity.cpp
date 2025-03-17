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
#define ROWS 5

void PlayerEntity::jump()
{
	if (!mIsGrounded)
	{
		return;
	}

	if (SetStates(State::Jumping)) {

		
		addForce(sf::Vector2f(0, -mJumpForce));
		mIsGrounded = false;
			mAnimator->Play("jump");
	
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
	mdirection = (int)Direction::Rigth;
	mSpeed = 0;
	mAcceleration = 45.f;
	mMaxSpeed = 180.f;
	mDeceleration = 50.f;
	mMass = 3;
	

	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(true);
	setKinetic(true);

	sf::Texture* texture = resourceManager->GetTexture("SpriteSheet");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}

	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(50, 50);
		mAnimator = new Animator(mSpriteSheet, 
		{
			new Animation("idle", 0, 6, 3),
			new Animation("annimation_idle", 7, 12,2),
			new Animation("jump", 12, 18, 10),
			new Animation("push", 19, 24, 1),
			new Animation("run",25,30,4),
		});



	mAnimator->Play("run");

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
		mdirection = (int)Direction::Rigth;
		mState = State::Running;
		if (mIsGrounded)
		{
			
			mAnimator->Play("run");
			mSpriteSheet->setScale(1, 1);
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
		mdirection = (int)Direction::Left;
		mState = State::Running;
		if (mIsGrounded)
		{
			
			mAnimator->Play("run");
			mSpriteSheet->setScale(-1, 1);
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
		SetStates(State::Idle);

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

	if (mState == State::Idle)
	{
		if (Timer->getElapsedTime().asSeconds() >= 10)
		{
			mAnimator->Play("annimation_idle");
			Timer->restart();
		}
		else
		{
			mAnimator->Play("idle");
		}
	}
	
		

}

bool PlayerEntity::SetStates(State State)
{
	int currentStateIndex = static_cast<int>(mState);
	int newStateIndex = static_cast<int>(State);

	if (mTransitions[currentStateIndex][newStateIndex] == 0)
		return false;

	mState = State;
	return true;
}
