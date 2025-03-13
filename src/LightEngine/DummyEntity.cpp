#include "DummyEntity.h"
#include "Managers/ResourceManager.h"

#include "Rendering/SpriteSheet.h"
#include "Rendering/Animation.h"
#include "Rendering/Animator.h"

#include <iostream>

#define COLUMNS 6
#define ROWS 1

void DummyEntity::OnInitialize()
{
	sf::Texture* texture = resourceManager->GetTexture("runAnimation");
	if (!texture) {
		std::cerr << "Erreur : Impossible de charger la texture 'runAnimation'." << std::endl;
	}

	mSpriteSheet = new SpriteSheet(texture, COLUMNS, ROWS);

	mAnimator = new Animator(mSpriteSheet,
		{
			new Animation("run", 0, 5, 3)
		});

	mAnimator->Play("run");
}
