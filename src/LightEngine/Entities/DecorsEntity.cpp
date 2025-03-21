#include "DecorsEntity.h"
#include "../Managers/ResourceManager.h"
#include "../RectangleCollider.h"
#include "../Rendering/SpriteSheet.h"

void DecorsEntity::onInitialize()
{
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
	setKinetic(false);

	sf::Texture* texture1 = resourceManager->GetTexture("props");
	if (!texture1) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}
}

void DecorsEntity::SetCurrent()
{

}
