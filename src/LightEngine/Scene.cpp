#include "Scene.h"

#include "Managers/GameManager.h"

int Scene::GetWindowWidth() const
{
	return gameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return gameManager->mWindowHeight;
}

float Scene::GetDeltaTime() const
{
	return gameManager->mDeltaTime;
}
