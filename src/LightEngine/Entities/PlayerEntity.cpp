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
#define ROWS 3

void PlayerEntity::jump()
{
	if (mIsGrounded) {
		addForce(sf::Vector2f(0, -mJumpForce));
		mIsGrounded = false;
	}
}

void PlayerEntity::onDownCollision()
{
	mForce.y = 0;
	mIsGrounded = true;
}

void PlayerEntity::onInitialize()
{
	mSpeed = 0;
	mAcceleration = 40.f;
	mMaxSpeed = 100.f;
	mDeceleration = 35.f;
	mMass = 3;

	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(true);
	setKinetic(true);

	sf::Texture* texture = resourceManager->GetTexture("player");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}

	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(50, 50);

	mAnimator = new Animator(mSpriteSheet,
		{
			new Animation("idle", 0, 5, 3),
			new Animation("jump", 6, 11, 3),
			new Animation("run", 12, 17, 3)
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

		isMovingRight = true;
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

		isMovingLeft = true;
	}
}

void PlayerEntity::Decelerate(float deltaTime)
{
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
	}
    
}




void PlayerEntity::onUpdate()
{
	if (inputManager->GetKeyDown("Jump"))
		jump();

	if (inputManager->GetAxis("Trigger") < 0)
		mMaxSpeed = 300;
	else
		mMaxSpeed = 100;

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

}
