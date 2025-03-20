
#include <SFML/Graphics.hpp>
#include <iostream>


#pragma region Scenes

#include "Scenes/SampleScene.h"
#include "Scenes/PhysicsScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/LvEditorScene.h"

#pragma endregion

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

	gameManager->CreateWindow(1920, 1080, "MiniStudio", 60, sf::Color::White);

	//gameManager->LaunchScene<PhysicsScene>();
	gameManager->LaunchScene<AnimationScene>();
	//gameManager->LaunchScene<LvEditorScene>();

	return 0;
}