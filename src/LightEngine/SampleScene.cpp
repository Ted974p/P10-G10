#include "SampleScene.h"

#include "DummyEntity.h"

#include "Debug.h"
#include <iostream>

void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<DummyEntity>(100, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetRigidBody(true);

	pEntity2 = CreateEntity<DummyEntity>(50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);

	pEntitySelected = nullptr;

	if (sf::Joystick::isConnected(0)) {
		std::cout << "Manette 0 connectée !" << std::endl;
	}

}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
	/*	if (pEntitySelected != nullptr) 
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}*/
	}

	// Gestion du mouvement avec le stick gauche
	

	if (sf::Joystick::isButtonPressed(0, 0)) 
	{
		pEntity1->SetSpeed(5);
	}
	float axeX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

	

	
}

void SampleScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{

	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
	
	float moveX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float moveY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	int speedZ = -sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

	pEntity1->SetDirection(moveX, moveY, (speedZ / 4) + 1);
	std::cout << "Position Axe z : " << speedZ << std::endl;
	

	if (moveX <= 5 && moveX >= -5)
	{
		if(moveY <= 5 && moveY >= -5)
		{
			pEntity1->SetSpeed(0);
		}
	}

		


	

}