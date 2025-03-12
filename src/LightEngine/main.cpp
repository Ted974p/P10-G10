
#include <SFML/Graphics.hpp>
#include <iostream>

#include "ManagersMacro.h"

#include "SampleScene.h"
#include "PhysicsScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    Managers* pInstance = Managers::GetInstance();

	gameManager->CreateWindow(1280, 720, "MiniStudio", 60, sf::Color::Black);
	
	gameManager->LaunchScene<PhysicsScene>();

	return 0;
}