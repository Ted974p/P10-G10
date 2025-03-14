#include "PlayerEntity.h"

#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"

#include <iostream>

#define COLUMNS 6
#define ROWS 3

void PlayerEntity::jump()
{
	std::cout << "jump" << std::endl;

	if (mIsGrounded) {
		addForce(sf::Vector2f(0, mJumpForce));
		mIsGrounded = false;
	}
}

void PlayerEntity::onDownCollision()
{
	mForce = sf::Vector2f(0, 0);
	mIsGrounded = true;
}

void PlayerEntity::onInitialize()
{
	mSpeed = 50;
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

void PlayerEntity::onUpdate()
{
	if (inputManager->GetKeyDown("jump"))
		jump();

	float horizontal = inputManager->GetAxis("Horizontal");

	sf::Vector2f direction(horizontal, 0);

	move(direction * getDeltaTime() * mSpeed);

	std::cout << getPosition().x << " , " << getPosition().y << std::endl;
}
