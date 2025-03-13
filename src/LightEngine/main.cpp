
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "SceneMS.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{

	//sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML works!");


	//sf::Texture texture;
	//if (!texture.loadFromFile("../.../src/LightEngine/image/test.png"))
	//{

	//	// error...
	//}
	//sf::Sprite robot(texture);

	//robot.setPosition(sf::Vector2f(50, 50));

	//while (window.isOpen())
	//{ 
	//	window.clear(sf::Color::Black);
	//	sf::Event event;
	//	while (window.pollEvent(event)) {
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//	}
	//	window.draw(robot);

	//	window.display();
	//}

    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "SampleScene", 60, sf::Color::Black);
	

	pInstance->LaunchScene<SceneMS>();

	return 0;
}