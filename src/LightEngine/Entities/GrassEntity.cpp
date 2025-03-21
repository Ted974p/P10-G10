#include "GrassEntity.h"
#include "../Managers/ResourceManager.h"
#include "../RectangleCollider.h"
#include "../Rendering/SpriteSheet.h"

void GrassEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
	setKinetic(false);

	sf::Texture* texture1 = resourceManager->GetTexture("props");
	if (!texture1) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
	mSpriteSheet = new SpriteSheet(texture1, 4, 6);
	mSpriteSheet->setPosition(30, 30);
	mSpriteSheet->setScale(0.64f, 0.64f);
	mSpriteSheet->setCurrent(20);
}
