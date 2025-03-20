#include "LevelScene.h"

#include "../Entities/PlayerEntity.h"
#include "../Entities/ObstacleEntity.h"
#include "../Entities/GroundEntity.h"
#include "../Entities/WallEntity.h"
#include "../Entities/MovingPlatform.h"
#include "../Entities/ButtonEntity.h"
#include "../Entities/DoorEntity.h"
#include "../Entities/LightEntity.h"
#include "../Entities/PlayerHead.h"
#include "../Entities/LiftableEntity.h"
#include "../Entities/TargetEntity.h"

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

#define COLLUMS 30
#define ROWS 18
#define SIZE 64

void LevelScene::onInitialize()
{
	// Level

	setNameLevel();
	createLv(mNameLevel);
	editEntitiesCreated();

	// Background

	Background* background_sky = createBackground();
	background_sky->setTexture("bg_sky");
	background_sky->setSpeed(1);

	Background* background3 = createBackground();
	background3->setTexture("bg_layer3");
	background3->setSpeed(2.3f);

	Background* background2 = createBackground();
	background2->setTexture("bg_layer2");
	background2->setSpeed(2);

	Background* background1 = createBackground();
	background1->setTexture("bg_layer1");
	background1->setSpeed(1.5f);

	//gameManager->getParallax()->setPlayer(mPlayer);

	// Camera

	mCamera = new Camera();
	GameManager* gm = gameManager;
	mCamera->setSize(gm->GetWindowWidth() * 0.8f, gm->GetWindowHeight() * 0.8f);
	mCamera->setDeadzone(150, 150, -50, 50);
	mCamera->setLimits(0, 1920, 0, 1080);
	mCamera->setCenter(mCamera->getSize().x / 2, mPlayer->getPosition().y);
}

void LevelScene::onUpdate()
{
	mCamera->update(gameManager->GetDeltaTime());
	gameManager->GetWindow()->setView(*mCamera);
}

void LevelScene::createLv(std::string name )
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
		if (s == 'G')
		{
			 GroundEntity* ground = createEntity<GroundEntity>();
			 ground->setPosition(posx, posy);
		}
		if (s == 'W')
		{
			WallEntity* ground = createEntity<WallEntity>();
			ground->setPosition(posx, posy);
		}
		if (s == '-')
		{		
		}
		if (s == 'M')
		{
			MovingPlatform* platform = createEntity<MovingPlatform>();
			platform->setPosition(posx, posy);
			platforms.push_back(platform);
		}
		if (s == 'C')
		{
			LiftableEntity* box = createEntity<LiftableEntity>();
			box->setPosition(posx, posy);
		}
		if (s == 'B')
		{
			ButtonEntity* button = createEntity<ButtonEntity>();
			button->setPosition(posx, posy);
			buttons.push_back(button);
		}
		if (s == 'T')
		{
			TargetEntity* target = createEntity<TargetEntity>();
			target->setPosition(posx, posy);
			targets.push_back(target);
		}
		if (s == 'D')
		{
			DoorEntity* door = createEntity<DoorEntity>();
			door->setPosition(posx, posy);
			doors.push_back(door);
		}
		if (s == 'P' && mPlayer == nullptr)
		{
			mPlayer = createEntity<PlayerEntity>();
			mPlayer->setPosition(posx, posy);
		}
	}
}

Camera* LevelScene::getCamera()
{
	return mCamera;
}
