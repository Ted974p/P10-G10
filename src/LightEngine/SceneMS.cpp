#include "SceneMS.h"

#include "DummyEntity.h"

#include "Debug.h"
#include <iostream>

void SceneMS::OnInitialize()
{
	mPlayer = CreateEntity<Player>(50, sf::Color::Blue);
	mPlayer->SetPosition(500, 500);
	mPlayer->SetRigidBody(true);

}

void SceneMS::OnEvent(const sf::Event& event)
{

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{

	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	}


}

void SceneMS::OnUpdate()
{

	float moveX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float moveY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	int speedZ = -sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

	std::cout << moveX << std::endl;

	if (moveX > 5)
	{
		mPlayer->MoveRight(GetDeltaTime());
	}

	if (moveX < -5)
	{
		mPlayer->MoveLeft(GetDeltaTime());
	}
	
}