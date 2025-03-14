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

void PlayerEntity::onInitialize()
{
	mSpeed = 0;
	mAcceleration = 10.f;
	mMaxSpeed = 100.f;
	mDeceleration = 25.f;

	addCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
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

	mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;

	isMovingRight = true;
}


void PlayerEntity::MoveLeft(float deltaTime)
{
	if (isMovingRight)
	{
		Decelerate(deltaTime);
	}

	else
	{
		mSpeed -= mAcceleration * deltaTime;
		if (mSpeed < -mMaxSpeed)
			mSpeed = -mMaxSpeed;

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
	float horizontal = inputManager->GetAxis("Horizontal");
	AnimationScene* aScene = getScene<AnimationScene>();
	float dt = aScene->getDeltaTime();
	std::cout << "fjkjsdinbnhvb  " << horizontal << std::endl;


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
