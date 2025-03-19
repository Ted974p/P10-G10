#include "LvEditorScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/ObstacleEntity.h"
#include "../Entities/GroundEntity.h"
#include "../Entities/MovingPlatform.h"
#include "../Entities/ButtonEntity.h"
#include "../Entities/DoorEntity.h"
#include "../Entities/LightEntity.h"
#include "../Entities/PlayerBody.h"
#include "../Entities/PlayerHead.h"
#include "../Entities/LiftableEntity.h"

#include "../CircleCollider.h"
#include "../RectangleCollider.h"

#include "../Utils/Debug.h"

#include "../Rendering/Parallax.h"
#include "../Rendering/Background.h"
#include "../Rendering/Camera.h"

#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
	
#include <iostream>
#include <fstream>

#define COLLUMS 20
#define ROWS 11
#define SIZE 100

Camera* LvEditorScene::getCamera()
{
	return mCamera;
}

void LvEditorScene::onInitialize()
{
	Background* background_sky = createBackground();
	background_sky->setTexture("bg_sky");
	background_sky->setSpeed(1);

	Background* background3 = createBackground();
	background3->setTexture("bg_layer3");
	background3->setSpeed(3);

	Background* background2 = createBackground();
	background2->setTexture("bg_layer2");
	background2->setSpeed(2);

	Background* background1 = createBackground();
	background1->setTexture("bg_layer1");
	background1->setSpeed(3);

	player = createEntity<PlayerEntity>();
	player->setPosition(0, 400);


	

	CreateLv("lvl");

	mCamera = new Camera();

	GameManager* gm = gameManager;
	mCamera->setSize(gm->GetWindowWidth() * 0.8f, gm->GetWindowHeight() * 0.8f);
	mCamera->setDeadzone(300, 300, -50, 50);
	mCamera->setLimits(0, 1920, 0, 1080);
	mCamera->setCenter(mCamera->getSize().x / 2, player->getPosition().y);

}

void LvEditorScene::onUpdate()
{
	mCamera->update(gameManager->GetDeltaTime());
	gameManager->GetWindow()->setView(*mCamera);

	
}

void LvEditorScene::CreateLv(std::string name )
{
	std::ifstream EditorFile(resourceManager->getTxt(name));
	char sight;
	int row = 0;
	int col = 0;
	if (EditorFile.is_open())
	{
		while (EditorFile >> sight) {
			{
				mSight.push_back(sight);
				mPositions.push_back({ col, row });
			}
			col++;
			if (col >= COLLUMS)
			{
				col = 0;
				row++;
			}
		}
	}
	else
	{
		std::cout << "Erreur d'ouverture ";
	}
	EditorFile.close();
	for (size_t i = 0; i < mSight.size(); ++i)
	{
		char s = mSight[i];
		Position pos = mPositions[i];

		int posx = SIZE * pos.x;
		int posy =  SIZE * pos.y;
		if (s == 'D')
		{
				ground = createEntity<GroundEntity>();
				ground->setPosition(posx, posy);
		}
		if (s == '-')
		{
		}
		if (s == 'M')
		{
			platform = createEntity<MovingPlatform>();
			platform->setPosition(posx, posy);
		}
		if (s == 'C')
		{
			box = createEntity<LiftableEntity>();
			box->setPosition(posx, posy);
		}
		if (s == 'B')
		{
			button = createEntity<ButtonEntity>();
			button->setPosition(posx, posy);

		}
		if (s == 'P')
		{
			door = createEntity<DoorEntity>();
			door->setPosition(posx, posy);
		}
	}
	button->SetDoor(door);
}
