
#include "PlayerEntity.h"

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
#include "../Scenes/AnimationScene.h"
#include "../Scenes/LvEditorScene.h"

#include <iostream>

#define COLUMNS 6
#define ROWS 5

void PlayerEntity::updateCameraWithDeadzones()
{

	Camera* camera = dynamic_cast<AnimationScene*>(getScene())->getCamera();
	//Camera* camera = dynamic_cast<LvEditorScene*>(getScene())->getCamera();
	if (!camera)
		return;

	sf::Vector2f playerPosition = getPosition();
	camera->ajustPositionDeadzone(playerPosition);
}

void PlayerEntity::jump()
{
	if (mIsGrounded) {
		float speedFactor = std::abs(mSpeed) / mMaxSpeed; // Normalise la vitesse (0 � 1)
		float adjustedJumpForce = mJumpForce + (speedFactor * mJumpForce * 0.2f); // Augmente l�g�rement en fonction de la vitesse
		addForce(sf::Vector2f(mSpeed * getDeltaTime() * 0.8f, -adjustedJumpForce));
		mState = State::Jumping;
		mIsGrounded = false;
	}
//	if (SetStates(State::Jumping)) {


	//}
}

void PlayerEntity::onDownCollision(Entity* other)
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
	mMass = 100;
	mJumpForce = 600;

	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setTag(int(Entity::TAG::Player));
	setRigidBody(true);
	setKinetic(true);
	//setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
	sf::Texture* texture = resourceManager->GetTexture("SpriteSheet1");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(50, 50);
	//mSpriteSheet->setPosition(32, 32);
	//mSpriteSheet->setScale(0.64f, 0.64f);
	mAnimator = new Animator(mSpriteSheet,
		{
		new Animation("idle", 0, 6, 3),
			new Animation("annimation_idle", 7, 12,2),
			new Animation("jump", 12, 18, 6),
			new Animation("push", 19, 24, 1),
			new Animation("run",25,30,4),
		});
	mAnimator->Play("idle");
}

void PlayerEntity::MoveRight(float deltaTime)
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
	//	mSpriteSheet->setScale(0.64f, 0.64f);
	}
}


void PlayerEntity::MoveLeft(float deltaTime)
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
		mState = State::Running;	
		mSpriteSheet->setScale(-1, 1);
		//mSpriteSheet->setScale(-0.64f, 0.64f);
	}
}

void PlayerEntity::Decelerate(float deltaTime)
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
	move(mSpeed * getDeltaTime(), 0);
	if (speedBoostActive && lightTimer.getElapsedTime().asSeconds() >= 5.0f)
	{
		isInLightEntity = false;
		speedBoostActive = false;
		std::cout << "Boost terminé, retour � la vitesse normale." << std::endl;
	}
	//std::cout << "Speed: " << mSpeed << " | Max Speed: " << mMaxSpeed << std::endl;
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
	updateCameraWithDeadzones();
}
