
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "SceneMS.h"

#include <cstdlib>
#include <crtdbg.h>

int main()
{
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "SampleScene", 60, sf::Color::Black);

	pInstance->LaunchScene<SceneMS>(); 

	return 0;
}