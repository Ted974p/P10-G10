
#include "PlayerEntity.h"

#include "../Entities/LiftableEntity.h"
#include "../Entities/PlayerHead.h"
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
#define ROWS 6

#define COLUMNS2 6
#define ROWS2 2

void PlayerEntity::updateCameraWithDeadzones()
{

	//Camera* camera = dynamic_cast<AnimationScene*>(getScene())->getCamera();
	Camera* camera = dynamic_cast<LevelScene*>(getScene())->getCamera();
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
}

void PlayerEntity::Drop()
{

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
		mForce.x = 0;
		mState = State::Idle;
	}

	mIsGrounded = true;

}

void PlayerEntity::onUpCollision(Entity* other)
{
	if (!other->isRigidBody())
		return;

	mForce.y = 0;
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

	//setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
	setTag(int(Entity::TAG::Player));
	setRigidBody(true);
	setKinetic(true);

	sf::Texture* texture = resourceManager->GetTexture("spritesheet1");
	sf::Texture* texture2 = resourceManager->GetTexture("spritesheet2");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(32, 32);

	mSpriteSheet2 = new SpriteSheet(texture2, COLUMNS2, ROWS2);
	mSpriteSheet2->setPosition(32, 25.6f);
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
			new Animation("jump", 25, 30, 2),
			new Animation("push", 7, 12, 1),
			new Animation("run",13,18,4),
			new Animation("Victory",19,24,2),
			new Animation("NoHead",31,36,2),
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
		//mSpriteSheet->setScale(1, 1);
	 	mSpriteSheet->setScale(0.64f, 0.64f);
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
		//mSpriteSheet->setScale(-1, 1);
		mSpriteSheet->setScale(-0.64f, 0.64f);
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
		float dt = getDeltaTime();

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

		std::cout << mDeceleration << std::endl;
		std::cout << "speed  " << mSpeed << std::endl;



		move(mSpeed * getDeltaTime(), 0);


		if (speedBoostActive && lightTimer.getElapsedTime().asSeconds() >= 5.0f)
		{
			isInLightEntity = false;
			speedBoostActive = false;
			std::cout << "Boost termin�, retour � la vitesse normale." << std::endl;
		}

		//std::cout << "Speed: " << mSpeed << " | Max Speed: " << mMaxSpeed << std::endl;
		//std::cout << "Player position: " << getPosition().x << ", " << getPosition().y << std::endl;

	}

	if (mState == State::Idle)
	{
		if (AnnimTimer.getElapsedTime().asSeconds() >= 10)
		{
			std::cout << "test";
			mAnimator->Play("annimation_idle");
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


		if (inputManager->GetKeyDown("Drop"))
		{
			mState = State::Drop;
		}


		//std::cout << "Speed: " << mSpeed << " | Max Speed: " << mMaxSpeed << std::endl;
		//std::cout << "Player position: " << getPosition().x << ", " << getPosition().y << std::endl;
	}

	if (mState == State::Idle)
	{
		if (AnnimTimer.getElapsedTime().asSeconds() >= 10)
		{ 
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
		if (!mPlayerActive)
		{
			mAnimator->Play("NoHead");
			mCurrentAnimation = "NoHead";
			AnnimTimer.restart();
		}
		if (closingTimer.getElapsedTime().asSeconds() >= DROP_ANIMATION_TIME && mCurrentAnimation == "Drop")
		{
			mSpriteSheet2->setVisible(false);
			mSpriteSheet->setVisible(true);

			/*if (DropTimer.getElapsedTime().asSeconds() >= 20.f)
			{
				mAnimator->Play("NoHead");
				mCurrentAnimation = "NoHead";
			}*/


			mAnimator->Play("NoHead");
			mCurrentAnimation = "NoHead";
			setPlayerActive(false);
			head = createEntity<PlayerHead>();
			head->setScale(0.64, 0.64);
			head->setPosition(getPosition().x + 70, getPosition().y);
			head->setPlayerActive(true);
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
	else if (mState == State::Drop)
	{
		mSpriteSheet->setVisible(false);
		mSpriteSheet2->setVisible(true);
		mAnimator2->Play("Drop");
		mCurrentAnimation = "Drop";

		closingTimer.restart();
	}
	if (mLiftedObject != nullptr)
	{
		std::cout << "c'est ok" << std::endl;
		if (inputManager->GetKeyDown("Lifting"))
		{
			std::cout << "Touche L détectée !" << std::endl;
			mLiftedObject->setPlayerLifting(nullptr);
			mLiftedObject->setPosition(getPosition().x + 150, getPosition().y);
			mLiftedObject->setKinetic(true);
			setLiftedObject(nullptr);
		}
	}
	mAnimator->Update(getDeltaTime());
	mAnimator2->Update(getDeltaTime());


	updateCameraWithDeadzones();

		if ((int)mState != 0)
			std::cout << (int)mState << std::endl;
}
