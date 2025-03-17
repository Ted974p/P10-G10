
#include "Scene.h"

#include "Managers/GameManager.h"

int Scene::getWindowWidth() const
{
	return gameManager->mWindowWidth;
}

int Scene::getWindowHeight() const
{
	return gameManager->mWindowHeight;
}

float Scene::getDeltaTime() const
{
	return gameManager->mDeltaTime;
}
