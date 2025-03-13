#include "SceneMS.h"

#include "DummyEntity.h"

#include "Debug.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

void SceneMS::OnInitialize()
{
	pEntity1 = CreateEntity<Entity>(50, sf::Color::Green);
	pEntity1->SetPosition(300, 300);

	mPlayer = CreateEntity<Player>(50, sf::Color::Blue);
	mPlayer->SetPosition(500, 500);
	mPlayer->SetRigidBody(true);

	mView.setSize(GetWindowWidth(), GetWindowHeight());
	mView.setCenter(mPlayer->GetPosition());
	
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		
	}
}

void SceneMS::OnUpdate()
{

	float moveX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float moveY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	int speedZ = -sf::Joystick::getAxisPosition(0, sf::Joystick::Z);


	if (moveX > 10)
	{
		mPlayer->MoveRight(GetDeltaTime());
	}

	else if (moveX < -10)
	{
		mPlayer->MoveLeft(GetDeltaTime());
	}

	else
	{
		mPlayer->Decelerate(GetDeltaTime());
	}

	sf::Vector2f targetPosition = mPlayer->GetPosition();
	sf::Vector2f currentViewPosition = mView.getCenter();

	float smoothFactor = 5.0f * GetDeltaTime(); 
	mView.setCenter(currentViewPosition + (targetPosition - currentViewPosition) * smoothFactor);

	GameManager* gm = GameManager::Get();
	if (gm)
	{
		sf::RenderWindow* window = gm->GetWindow();
		if (window)
		{
			window->setView(mView);
		}
	}
}