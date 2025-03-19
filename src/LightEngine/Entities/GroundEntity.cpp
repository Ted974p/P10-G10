#include "GroundEntity.h"

#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
void GroundEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
	setRigidBody(true);
	setKinetic(false);


	setTag(int(Entity::TAG::Plateform));

	sf::Texture* texture1 = resourceManager->GetTexture("ground");
	if (!texture1) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	sf::Texture* texture2 = resourceManager->GetTexture("ground");
	if (!texture2) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture1, 1, 1);
	mSpriteSheet->setPosition(50, 50);

}