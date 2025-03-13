#include "PlayerEntity.h"

#include "Managers/ResourceManager.h"
#include "Managers/InputManager.h"

#include "RectangleCollider.h"

#include "Rendering/SpriteSheet.h"
#include "Rendering/Animation.h"
#include "Rendering/Animator.h"

#include <iostream>

#define COLUMNS 6
#define ROWS 3

void PlayerEntity::OnInitialize()
{
	mSpeed = 50;

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
			new Animation("run", 11, 17, 3)
		});

	mAnimator->Play("idle");
}

void PlayerEntity::OnUpdate()
{
	float horizontal = inputManager->GetAxis("Horizontal");
	float vertical = inputManager->GetAxis("Vertical");

	sf::Vector2f direction1(horizontal, vertical);

	move(direction1 * getDeltaTime() * mSpeed);
}
