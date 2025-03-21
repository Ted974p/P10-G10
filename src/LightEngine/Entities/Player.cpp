
#include "Player.h"

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

void Player::updateCameraWithDeadzones()
{

	//Camera* camera = dynamic_cast<AnimationScene*>(getScene())->getCamera();
	Camera* camera = dynamic_cast<LevelScene*>(getScene())->getCamera();
	if (!camera)
		return;

	sf::Vector2f playerPosition = getPosition();
	camera->ajustPositionDeadzone(playerPosition);
}

void Player::jump()
{
	if (mIsGrounded) {
		float speedFactor = std::abs(mSpeed) / mMaxSpeed; // Normalise la vitesse (0 � 1)
		float adjustedJumpForce = mJumpForce + (speedFactor * mJumpForce * 0.2f); // Augmente l�g�rement en fonction de la vitesse
		addForce(sf::Vector2f(mSpeed * getDeltaTime() * 0.8f, -adjustedJumpForce));

		mIsGrounded = false;
		SetStates(State::Jumping);
	}
}

void Player::Drop()
{

}


void Player::onDownCollision(Entity* other)
{
	if (!other->isRigidBody())
		return;

	if (mForce.y < 0)
		return;

	mForce.y = 0;

	if (!mIsGrounded) // V�rifie si on vient juste d'atterrir
	{
		mJustLanded = true;
		// Active le timer
		mForce.x = 0;
	}

	mIsGrounded = true;
	SetStates(State::Idle);

}

void Player::onUpCollision(Entity* other)
{
	if (!other->isRigidBody())
		return;

	mForce.y = 0;
}

bool Player::SetStates(State State)
{
	int currentStateIndex = static_cast<int>(mState);
	int newStateIndex = static_cast<int>(State);

	if (mTransitions[currentStateIndex][newStateIndex] == 0)
		return false;

	mState = State;
	return true;
}

void Player::onInitialize()
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
	sf::Texture* texture = resourceManager->GetTexture("SpriteSheetFinal");
	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(32, 32);
	mSpriteSheet->setScale(0.63, 0.63);
	mAnimator = new Animator(mSpriteSheet,
		{
		new Animation("idle", 0, 6, 3),
			new Animation("push", 7, 12, 1),
			new Animation("run",13,18,4),
			new Animation("Idle_Annimation",19,24,2),
			new Animation("jump", 25, 30, 2),
			new Animation("Desactivate",31,3,1),

		});
	mAnimator->Play("Desactivate");
}

void Player::MoveRight(float deltaTime)
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
		SetStates(State::Running);
		//mSpriteSheet->setScale(1, 1);
		mSpriteSheet->setScale(0.64f, 0.64f);
	}
}


void Player::MoveLeft(float deltaTime)
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
		SetStates(State::Running);
		//mSpriteSheet->setScale(-1, 1);
		mSpriteSheet->setScale(-0.64f, 0.64f);
	}
}

void Player::Decelerate(float deltaTime)
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
		SetStates(State::Idle);
	}
}

void Player::setInLightEntity(bool value)
{
	if (value)
	{
		isInLightEntity = true;
		speedBoostActive = true;
	}
	else
	{
		isInLightEntity = false;
		speedBoostActive = false;
	}
}

void Player::onUpdate()
{
	if (mState == State::Morphing)
	{
		if (Morf)
		{
			return;
		}
		if (MorphingTime.getElapsedTime().asSeconds() >= 5)
		{
			robotDesactivate();
			Morf = true;
			head = createEntity<PlayerHead>();
			//head->Set(this);

		}
	}
	if (mState == State::DeMorphing)
	{

		if (MorphingTime.getElapsedTime().asSeconds() >= 5)
		{
			robotActivation();
			Morf = false;
			head->destroy();
		}
		if (Morf)
		{

			return;
		}
	}
	if (mJustLanded)
	{
		mLandingTimer -= getDeltaTime();
		if (mLandingTimer <= 0)
		{
			mJustLanded = false; // D�sactive l'effet apr�s un moment
		}
	}
	if (mState != State::Morphing && mState != State::DeMorphing)
	{

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

		if (mState == State::Drop)
		{
			SetStates(State::Idle);
		}
		if (mState == State::Idle)
		{
			if (AnnimFlower.getElapsedTime().asSeconds() >= 10)
			{

				mAnimator->Play("annimation_idle");
			}
			else if (AnnimFlower.getElapsedTime().asSeconds() < 10)
			{
				mAnimator->Play("idle");
			}
			if (AnnimFlower.getElapsedTime().asSeconds() >= 20)
			{
				AnnimFlower.restart();
			}
			if (inputManager->GetKeyDown("Drop"))
			{
				Morphing();
			}
		}
		else if (mState == State::Jumping)
		{
			mAnimator->Play("jump");

		}
		else if (mState == State::Running)
		{
			mAnimator->Play("run");

		}
		if (mState == State::Lifting)
		{
			std::cout << "c'est ok" << std::endl;
			if (inputManager->GetKeyDown("Lifting"))
			{
				std::cout << "Touche L détectée !" << std::endl;
				//mLiftedObject->setPlayerLifting(nullptr);
				mLiftedObject->setPosition(getPosition().x + 150, getPosition().y);
				SetStates(State::Drop);
				mLiftedObject->setKinetic(true);
				setLiftedObject(nullptr);
			}
		}
		move(mSpeed * getDeltaTime(), 0);
		updateCameraWithDeadzones();
	}
}

void Player::Morphing()
{
	sf::Texture* texture = resourceManager->GetTexture("SpriteSheetFinal2");
	mSpriteSheet = new SpriteSheet(texture, COLUMNS2, ROWS2);
	mSpriteSheet->setPosition(32, 32);
	mSpriteSheet->setScale(0.63, 0.63);
	mAnimator = new Animator(mSpriteSheet,
		{
		new Animation("Drop", 0, 5, 1,false),
			new Animation("Take", 6,11 ,2),
		});
	mAnimator->Play("Drop");
	mState = State::Morphing;
	MorphingTime.restart();
}

void Player::DeMorphing()
{
	sf::Texture* texture = resourceManager->GetTexture("SpriteSheetFinal2");
	mSpriteSheet = new SpriteSheet(texture, COLUMNS2, ROWS2);
	mSpriteSheet->setPosition(32, 32);
	mSpriteSheet->setScale(0.64, 0.64);
	mAnimator = new Animator(mSpriteSheet,
		{
		new Animation("Drop", 0, 5, 1,false),
			new Animation("Take", 6,11 ,1),
		});
	mAnimator->Play("Take");
	mState = State::DeMorphing;
	MorphingTime.restart();


}

void Player::robotDesactivate()
{
	sf::Texture* texture = resourceManager->GetTexture("SpriteSheetFinal");
	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(32, 32);
	mSpriteSheet->setScale(0.63, 0.63);
	mAnimator = new Animator(mSpriteSheet,
		{
		new Animation("idle", 0, 6, 3),
			new Animation("push", 7, 12, 1),
			new Animation("run",13,18,4),
			new Animation("Idle_Annimation",19,24,2),
			new Animation("jump", 25, 30, 2),
			new Animation("Desactivate",31,36,1),

		});
	mAnimator->Play("Desactivate");
	Morf = true;
}

void Player::robotActivation()
{
	sf::Texture* texture = resourceManager->GetTexture("SpriteSheetFinal");
	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);
	mSpriteSheet->setPosition(32, 32);
	mSpriteSheet->setScale(0.63, 0.63);
	mAnimator = new Animator(mSpriteSheet,
		{
		new Animation("idle", 0, 6, 3),
			new Animation("push", 7, 12, 1),
			new Animation("run",13,18,4),
			new Animation("Idle_Annimation",19,24,2),
			new Animation("jump", 25, 30, 2),
			new Animation("Desactivate",31,36,1),

		});
	mAnimator->Play("idle");
	Morf = false;

}
