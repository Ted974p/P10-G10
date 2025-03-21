#include "LiftableEntity.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include <iostream>

void LiftableEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
	setRigidBody(true);
	setKinetic(true);

	sf::Texture* texture1 = resourceManager->GetTexture("props");
	if (!texture1) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture1, 4, 6);
	mSpriteSheet->setPosition(32, 32);
	mSpriteSheet->setScale(0.64f, 0.64f);
	mSpriteSheet->setCurrent(1);
	mMass = 100;
}

void LiftableEntity::onDownCollision(Entity* other)
{
	if (!other->isRigidBody())
		return;

	if (mForce.y < 0)
		return;

	mForce.y = 0;

	mIsGrounded = true;
}

void LiftableEntity::onCollision(Entity* _other)
{
	if (inputManager->GetKeyDown("Lifting"))
	{
		if (_other->isTag((int)Entity::TAG::Player))
		{
			setPlayerLifting(dynamic_cast<PlayerEntity*>(_other));
			mPlayerLifting->setLiftedObject(this);
		}
	}
}
void LiftableEntity::onUpdate()
{
	if (mPlayerLifting != nullptr)
	{
		setPosition(mPlayerLifting->getPosition().x, mPlayerLifting->getPosition().y - 100);
	}
}
