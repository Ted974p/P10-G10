#include "GroundEntity.h"

#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
void GroundEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
	setRigidBody(true);
	setKinetic(false);
	setTag(int(Entity::TAG::Plateform));

	sf::Texture* texture1 = resourceManager->GetTexture("ground");
	if (!texture1) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture1, 1, 1);
	mSpriteSheet->setPosition(32, 32);
	mSpriteSheet->setScale(0.64f, 0.64f);
}