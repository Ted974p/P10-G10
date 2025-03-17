
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

void PlayerEntity::onDownCollision(Entity* other)
{
	if (!other->isRigidBody())
	
		return;
	

	if (mForce.y < 0)
		return;

	mForce.y = 0;
	mIsGrounded = true;
}

void PlayerEntity::onInitialize()
{
	mSpeed = 0;
	mAcceleration = 45.f;
	mMaxSpeed = 180.f;
	mDeceleration = 50.f;
	mMass = 3;

	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setTag(int(Entity::TAG::Player));
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

	mColliderCast = dynamic_cast<RectangleCollider*>(getCollider());

	sf::Vector2f pos = getPosition();
	sf::Vector2f size = mColliderCast->getSize();
	mGroundCheck = new RectangleCollider(this, pos + sf::Vector2f(0, size.y + 5), sf::Vector2f(size.x, 5));
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
	}

}

void PlayerEntity::onUpdate()
{
	if (inputManager->GetKeyDown("Jump"))
		jump();

	if (mLiftedObject != nullptr)
	{
		if (inputManager->GetKeyDown("Lifting"))
		{
			mLiftedObject->setPlayerLifting(nullptr);
			mLiftedObject->setPosition(getPosition().x + 20, getPosition().y);
			setLiftedObject(nullptr);
		}
	}

	if (inputManager->GetAxis("Trigger") < 0)
	{
		mMaxSpeed = 180.f;
		mAcceleration = 70.f;
		mDeceleration = 80.f;
	}
	else
	{
		mMaxSpeed = 100.f;
		mAcceleration = 45.f;


		if (mSpeed > 100 || mSpeed < -100)
			mDeceleration = 70.f;
		else
			mDeceleration = 50.f;
	}


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

	if (mSpeed < -1 || mSpeed > 1)
	{
		move(mSpeed * getDeltaTime(), 0);
	}

	checkIfGrounded();
}

void PlayerEntity::checkIfGrounded()
{
	sf::Vector2f pos = getPosition();
	sf::Vector2f size = mColliderCast->getSize();

	mGroundCheck->setPosition(pos + sf::Vector2f(0, size.y + 5));

	for (Entity* entity : gameManager->getEntities())
	{
		if (entity == this) continue;

		if (mGroundCheck->isColliding(entity->getCollider()))
		{
			mIsGrounded = true;
			return;
		}
	}

	mIsGrounded = false;
}
