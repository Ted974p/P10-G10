
#include "Scene.h"

#include "Managers/GameManager.h"

#include "Rendering/Background.h"

int Scene::getWindowWidth() const
{
	return gameManager->mWindowWidth;
}

int Scene::getWindowHeight() const
{
	return gameManager->mWindowHeight;
}

Background* Scene::createBackground()
{	
	Background* newBackground = new Background();

	gameManager->addBackground(newBackground);

	return newBackground;
}

float Scene::getDeltaTime() const
{
	return gameManager->mDeltaTime;
}
