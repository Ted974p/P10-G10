#include "WallEntity.h"

#include "../Managers/ResourceManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"

void WallEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
	setRigidBody(true);
	setKinetic(false);
	setTag(int(Entity::TAG::Plateform));

	sf::Texture* texture1 = resourceManager->GetTexture("props");
	if (!texture1) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture1, 4, 6);
	mSpriteSheet->setPosition(32, 32);
	mSpriteSheet->setScale(2, 0.65f);
	mSpriteSheet->setCurrent(6);

}

void WallEntity::setSkin(int _skin) //pour le nom, il est 6h du mat...
{
	if (_skin == 0)
		mSpriteSheet->setCurrent(2);
	else if (_skin == 1)
		mSpriteSheet->setCurrent(6);

	// filoutage pour camoufler les problèmes de spritesheet
	sf::Vector2f hv = mSpriteSheet->getHV();
	sf::Vector2f xy = mSpriteSheet->getXY();
	mSpriteSheet->setTextureRect(sf::IntRect(xy.x * hv.x + 2, xy.y * hv.y, hv.x - 2, hv.y));
}
