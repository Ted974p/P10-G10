#include "GroundEntity2.h"
#include "../Managers/ResourceManager.h"
#include "../RectangleCollider.h"
#include "../Rendering/SpriteSheet.h"

void GroundEntity2::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 25)));
	setRigidBody(true);
	setKinetic(false);
	setTag(int(Entity::TAG::Plateform));

	sf::Texture* texture1 = resourceManager->GetTexture("props");
	if (!texture1) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture1, 4, 6);
	mSpriteSheet->setPosition(30, -15);
	mSpriteSheet->setScale(0.64f, 0.55f);
	mSpriteSheet->setCurrent(14);

	// filoutage pour camoufler les probl�mes de spritesheet
	sf::Vector2f hv = mSpriteSheet->getHV();
	sf::Vector2f xy = mSpriteSheet->getXY();
	mSpriteSheet->setTextureRect(sf::IntRect(xy.x * hv.x, xy.y * hv.y + 2, hv.x, hv.y));
}
