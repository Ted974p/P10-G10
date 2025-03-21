
#include <SFML/Graphics.hpp>
#include <iostream>


#pragma region Scenes

#include "Scenes/Levels/Level1.h"
#include "Scenes/Levels/Level2.h"
#include "Scenes/Levels/Level3.h"
#include "Scenes/Levels/Level4.h"

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

	gameManager->LaunchScene<Level4>();

	return 0;
}