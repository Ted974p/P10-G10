#include "PlayerHead.h"

#include "../Entities/LiftableEntity.h"
#include "../Entities/LightEntity.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include "../Scenes/AnimationScene.h"

#include <iostream>

#define COLUMNS 6
#define ROWS 1

void PlayerHead::jump()
{
	if (mIsGrounded) {
		addForce(sf::Vector2f(0, -mJumpForce));
		mIsGrounded = false;
	}
}

void PlayerHead::onDownCollision(Entity* other)
{
	if (!other->isRigidBody())
		return;

	//std::cout << "Le Player est dans la zone" << std::endl;
	if (mForce.y < 0)
		return;

	mForce.y = 0;
	mIsGrounded = true;
}

void PlayerHead::onInitialize()
{
	mSpeed = 0;
	mAcceleration = 45.f;
	mMaxSpeed = 180.f;
	mDeceleration = 50.f;
	mMass = 3;

	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(57, 57)));
	setTag(int(Entity::TAG::Player));
	setRigidBody(true);
	setKinetic(true);

	sf::Texture* texture = resourceManager->GetTexture("SpriteSheetFinalHead");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}

	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setScale(1.f, 1.f);
	mSpriteSheet->setPosition(28, 20);

	mAnimator = new Animator(mSpriteSheet,
		{
			new Animation("idle", 0, 5, 3),
			new Animation("jump", 6, 11, 3),
			new Animation("run", 12, 17, 3)
		});

	mAnimator->Play("idle");

	mColliderCast = dynamic_cast<RectangleCollider*>(getCollider());

	sf::Vector2f pos = getPosition();
	sf::Vector2f size = mColliderCast->getSize();
	mGroundCheck = new RectangleCollider(this, pos + sf::Vector2f(0, size.y + 5), sf::Vector2f(size.x, 5));
}

void PlayerHead::MoveRight(float deltaTime)
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


void PlayerHead::MoveLeft(float deltaTime)
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

void PlayerHead::Decelerate(float deltaTime)
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

void PlayerHead::setInLightEntity(bool value)
{
	if (value)
	{
		isInLightEntity = true;
		lightTimer.restart();
		speedBoostActive = true;
	}
	else
	{
		isInLightEntity = false;
		speedBoostActive = false;
	}
}

void PlayerHead::onUpdate()
{
	if (inputManager->GetKeyDown("Jump"))
		jump();

	if (inputManager->GetAxis("Trigger") < 0 || isInLightEntity)
		mMaxSpeed = 180.f;
	else
		mMaxSpeed = 100.f;

	float horizontal = inputManager->GetAxis("Horizontal");

	AnimationScene* aScene = getScene<AnimationScene>();
	float dt = aScene->getDeltaTime();

	if (mLiftedObject != nullptr)
	{
		std::cout << "c'est ok" << std::endl;

		if (inputManager->GetKeyDown("Lifting"))
		{
			std::cout << "dfsdfdsfdsf" << std::endl;
			mLiftedObject->setPlayerLifting(nullptr);
			mLiftedObject->setPosition(getPosition().x + 150, getPosition().y);
			mLiftedObject->setHasGravity(true);
			mLiftedObject->setKinetic(true);
			setLiftedObject(nullptr);
		}
	}

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

	if (speedBoostActive && lightTimer.getElapsedTime().asSeconds() >= 5.0f)
	{
		isInLightEntity = false;
		speedBoostActive = false;
		std::cout << "Boost terminé, retour à la vitesse normale." << std::endl;
	}

	checkIfGrounded();

	std::cout << "Speed: " << mSpeed << " | Max Speed: " << mMaxSpeed << std::endl;
	//std::cout << "Player position: " << getPosition().x << ", " << getPosition().y << std::endl;
}

void PlayerHead::checkIfGrounded()
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
