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
		mPlayer->SwitchFall();

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mPlayer->MoveLeft(GetDeltaTime());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mPlayer->MoveRight(GetDeltaTime());
	}
	

}

void SceneMS::OnUpdate()
{
	Debug::DrawRectangle(50.f, 50.f, 100.f, 20.f, sf::Color::White);

	float moveX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float moveY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	int speedZ = -sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

	std::cout << moveX;


	if (moveX > 10)
	{
		
	}

	else if (moveX < -10)
	{
		
	}

	else
	{
		
	}

	// Met � jour la position de la vue en douceur
	sf::Vector2f targetPosition = mPlayer->GetPosition();
	sf::Vector2f currentViewPosition = mView.getCenter();

	// Ajout d'une interpolation (lerp) pour lisser le mouvement
	float smoothFactor = 5.0f * GetDeltaTime(); // Ajuste selon tes besoins
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
	if (mPlayer->GetPosition().y >= GetWindowHeight())
	{
		mPlayer->SwitchFall();
	}
	mPlayer->Fall(GetDeltaTime());

	if (mPlayer->isMoving)
	{
		mPlayer->Decelerate(GetDeltaTime());
	}
}