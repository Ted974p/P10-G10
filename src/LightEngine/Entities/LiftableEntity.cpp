#include "LiftableEntity.h"
#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include <iostream>

void LiftableEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(true);
	setKinetic(true);

	sf::Texture* texture1 = resourceManager->GetTexture("Box");
	if (!texture1) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture1, 1, 1);
	mSpriteSheet->setPosition(50, 50);

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

	if (_other->isTag((int)Entity::TAG::Player))
	{
		setPlayerLifting(dynamic_cast<PlayerEntity*>(_other));
		mPlayerLifting->setLiftedObject(this);
	}
}


void LiftableEntity::onUpdate()
{

	if (mPlayerLifting != nullptr)
	{
		setPosition(mPlayerLifting->getPosition().x, mPlayerLifting->getPosition().y - 100);
	}

}
