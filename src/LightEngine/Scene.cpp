#include "Scene.h"

#include "../Managers/GameManager.h"

int Scene::getWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::getWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

float Scene::getDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}