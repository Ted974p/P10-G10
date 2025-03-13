
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"

#include "SampleScene.h"
#include "PhysicsScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "MiniStudio", 60, sf::Color::Black);
	
	pInstance->LaunchScene<PhysicsScene>();

	return 0;
}