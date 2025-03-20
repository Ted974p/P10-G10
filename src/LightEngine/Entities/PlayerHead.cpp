#include "PlayerHead.h"

#include "../Entities/LiftableEntity.h"
#include "../Entities/LightEntity.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/GameManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include "../Rendering/Camera.h"
#include "../Scenes/LevelScene.h"

#include <iostream>


#define COLUMNS 6
#define ROWS 1

#define COLUMNS2 6
#define ROWS2 2

void PlayerHead::updateCameraWithDeadzones()
{

	Camera* camera = dynamic_cast<LevelScene*>(getScene())->getCamera();
	//Camera* camera = dynamic_cast<LvEditorScene*>(getScene())->getCamera();
	if (!camera)
		return;

	sf::Vector2f playerPosition = getPosition();
	camera->ajustPositionDeadzone(playerPosition);
}

void PlayerHead::jump()
{
	if (mIsGrounded) {
		float speedFactor = std::abs(mSpeed) / mMaxSpeed; // Normalise la vitesse (0 � 1)
		float adjustedJumpForce = mJumpForce + (speedFactor * mJumpForce * 0.2f); // Augmente l�g�rement en fonction de la vitesse
		addForce(sf::Vector2f(mSpeed * getDeltaTime() * 0.8f, -adjustedJumpForce));
		mIsGrounded = false;
	}
}



void PlayerHead::onDownCollision(Entity* other)
{
	if (!other->isRigidBody())
		return;

	if (mForce.y < 0)
		return;

	mForce.y = 0;

	if (!mIsGrounded) // V�rifie si on vient juste d'atterrir
	{
		mJustLanded = true;
		mLandingTimer = LANDING_DECELERATION_TIME; // Active le timer
		std::cout << "rded" << std::endl;
		mForce.x = 0;
	}

	mIsGrounded = true;
	mState = State::Idle;
}


bool PlayerHead::SetStates(State State)
{
	int currentStateIndex = static_cast<int>(mState);
	int newStateIndex = static_cast<int>(State);

	if (mTransitions[currentStateIndex][newStateIndex] == 0)
		return false;

	mState = State;
	return true;
}

void PlayerHead::onInitialize()
{
	mSpeed = 0;
	mAcceleration = 45.f;
	mMaxSpeed = 180.f;
	mDeceleration = 50.f;
	mMass = 100;
	mJumpForce = 600;

	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setTag(int(Entity::TAG::Head));
	setRigidBody(true);
	setKinetic(true);

	sf::Texture* texture = resourceManager->GetTexture("SpriteSheetFinalHead");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(50, 70);

	mAnimator = new Animator(mSpriteSheet,
		{
		new Animation("idle", 0, 6, 3),
			new Animation("annimation_idle", 1, 6,2),
			new Animation("jump", 25, 30, 2),
			new Animation("push", 7, 12, 1),
			new Animation("run",13,18,4),
			new Animation("Victory",19,24,2),
			new Animation("NoHead",31,36,2),
		});
	mAnimator->Play("idle");

}

void PlayerHead::MoveRight(float deltaTime)
{
	if (isMovingLeft)
	{
		mDeceleration = 180.f;
		Decelerate(deltaTime);
	}
	else
	{
		if (mSpeed > mMaxSpeed)
			Decelerate(deltaTime);
		else
		{
			mSpeed += mAcceleration * deltaTime;
			isMovingRight = true;
		}
	}
	if (mIsGrounded)
	{
		mState = State::Running;
		mSpriteSheet->setScale(1, 1);
	}
}


void PlayerHead::MoveLeft(float deltaTime)
{
	if (isMovingRight)
	{
		mDeceleration = 180.f;
		Decelerate(deltaTime);
	}
	else
	{
		if (mSpeed < -mMaxSpeed)
			Decelerate(deltaTime);
		else
			mSpeed -= mAcceleration * deltaTime;

		isMovingLeft = true;
	}
	if (mIsGrounded)
	{
		mSpriteSheet->setScale(-1, 1);
		//mSpriteSheet->setScale(-0.64f, 0.64f);
	}
}

void PlayerHead::Decelerate(float deltaTime)
{

	mDeceleration = mJustLanded ? mLandingDeceleration : mDeceleration;
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
	if (mPlayerActive)
	{
		if (mJustLanded)
		{
			mLandingTimer -= getDeltaTime();
			if (mLandingTimer <= 0)
			{
				mJustLanded = false; // D�sactive l'effet apr�s un moment
			}
		}
		if (inputManager->GetKeyDown("Jump"))
			jump();
		if (inputManager->GetAxis("Trigger") < 0 || isInLightEntity)
		{
			mMaxSpeed = 200.f;
			mAcceleration = 90.f;
			mDeceleration = 130.f;
		}
		else
		{
			mMaxSpeed = 130.f;
			mAcceleration = 70.f;

			if (mSpeed > 100 || mSpeed < -100)
				mDeceleration = 100.f;
			else
				mDeceleration = 75.f;
		}
		float horizontal = inputManager->GetAxis("Horizontal");
		LevelScene* aScene = getScene<LevelScene>();

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
		move(mSpeed * getDeltaTime(), 0);
		if (speedBoostActive && lightTimer.getElapsedTime().asSeconds() >= 5.0f)
		{
			isInLightEntity = false;
			speedBoostActive = false;
			std::cout << "Boost terminé, retour � la vitesse normale." << std::endl;
		}
	}
}


