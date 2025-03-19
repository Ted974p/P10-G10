#include "PlayerEntity.h"

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
#define ROWS 6

#define COLUMNS2 6
#define ROWS2 2

void PlayerEntity::jump()
{
	if (mIsGrounded) {
		mState = State::Jumping;
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
	mState = State::Idle;

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

	sf::Texture* texture = resourceManager->GetTexture("SpriteSheetFinal");
	sf::Texture* texture2 = resourceManager->GetTexture("SpriteSheetFinal2");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}

	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(50, 50);

	mSpriteSheet2 = new SpriteSheet(texture2, COLUMNS2, ROWS2);
	mSpriteSheet2->setPosition(50, 50);
	mSpriteSheet2->setVisible(false);

	mAnimator2 = new Animator(mSpriteSheet2,
		{
		new Animation("idle", 0, 6, 3),
			new Animation("Drop", 1, 6,2),
		});

	mAnimator = new Animator(mSpriteSheet,
		{
		new Animation("idle", 0, 6, 3),
			new Animation("annimation_idle", 1, 6,2),
			new Animation("jump", 24, 30, 10),
			new Animation("push", 7, 12, 1),
			new Animation("run",13,18,4),
			new Animation("Victory",31,36,2),
			new Animation("Lachetamere",31,36,2),
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
			if (mIsGrounded)
			{
			mState = State::Running;
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

		isMovingLeft = true;
		if (mIsGrounded)
		{

			mState = State::Running;	
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
		mState = State::Idle;
	}
    
}

void PlayerEntity::setInLightEntity(bool value)
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

void PlayerEntity::onUpdate()
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
		std::cout << "Boost terminé, retour � la vitesse normale." << std::endl;
	}

	std::cout << "Speed: " << mSpeed << " | Max Speed: " << mMaxSpeed << std::endl;
	//std::cout << "Player position: " << getPosition().x << ", " << getPosition().y << std::endl;

	if (mState == State::Idle)
	{
		if (AnnimTimer.getElapsedTime().asSeconds() >= 10)
		{
			std::cout << "test";
			mAnimator->Play("annimation_idle");

		}
		else if (AnnimTimer.getElapsedTime().asSeconds() < 10)
		{
			mAnimator->Play("idle");
		}
		if (AnnimTimer.getElapsedTime().asSeconds() >= 20)
		{
			AnnimTimer.restart();
		}
		if (inputManager->GetKeyDown("Drop"))
		{
			std::cout << "aled" << std::endl;
			mSpriteSheet->setVisible(false);
			mSpriteSheet2->setVisible(true);
			mAnimator2->Play("Drop");
		}
	}
	else if (mState == State::Jumping)
	{
		mAnimator->Play("jump");
		AnnimTimer.restart();
	}
	else if (mState == State::Running)
	{
		mAnimator->Play("run");
		AnnimTimer.restart();
	}
	if (mLiftedObject != nullptr)
	{
		std::cout << "c'est ok" << std::endl;
		if (inputManager->GetKeyDown("Lifting"))
		{
			std::cout << "Touche L détectée !" << std::endl;
			mLiftedObject->setPlayerLifting(nullptr);
			mLiftedObject->setPosition(getPosition().x + 150, getPosition().y);
			mLiftedObject->setHasGravity(true);
			mLiftedObject->setKinetic(true);
			setLiftedObject(nullptr);
		}
	}
}
