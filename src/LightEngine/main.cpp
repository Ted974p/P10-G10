
#include <SFML/Graphics.hpp>
#include <iostream>

#include "SampleScene.h"
#include "PhysicsScene.h"
#include "GameManager.h"
#include "SceneMS.h"

#include <cstdlib>
#include <crtdbg.h>

#include "Managers/GameManager.h"
#include "Managers/InputManager.h"
#include "Managers/ResourceManager.h"

int main() 
{
	static GameManager* pGameManager = GameManager::GetInstance();
	static InputManager* pInputManager = InputManager::GetInstance();
	static ResourceManager* pResourceManager = ResourceManager::GetInstance();

	pInstance->CreateWindow(1280, 720, "SampleScene", 60, sf::Color::Black);
	
	pInstance->LaunchScene<SampleScene>();

	return 0;
}