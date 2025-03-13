#include <SFML/Graphics.hpp>
#include <iostream>
#include "SampleScene.h"
#include "PhysicsScene.h"
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

	gameManager->CreateWindow(1280, 720, "MiniStudio", 60, sf::Color::Black);
	
	gameManager->LaunchScene<PhysicsScene>();

	return 0;
}