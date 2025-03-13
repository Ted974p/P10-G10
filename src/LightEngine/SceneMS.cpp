#include "SceneMS.h"

#include "DummyEntity.h"
#include "Utils/Debug.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

void SceneMS::OnInitialize()
{
	pEntity1 = createEntity<Entity>(sf::Color::Green);
	pEntity1->setPosition(300, 300);

	mPlayer = createEntity<Player>(sf::Color::Blue);
	mPlayer->setPosition(500, 500);
	mPlayer->setRigidBody(true);

	pPlateformer = createEntity<Plateformer>(sf::Color::Red);

	mView.setSize(GetWindowWidth(), GetWindowHeight());
	mView.setCenter(mPlayer->getPosition());
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
	Debug::DrawRectangle(100.f, 50.f, 400.f, 200.f, sf::Color::White);

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
	sf::Vector2f targetPosition = mPlayer->getPosition();
	sf::Vector2f currentViewPosition = mView.getCenter();

	// Ajout d'une interpolation (lerp) pour lisser le mouvement
	float smoothFactor = 5.0f * GetDeltaTime(); // Ajuste selon tes besoins
	mView.setCenter(currentViewPosition + (targetPosition - currentViewPosition) * smoothFactor);

	if (gameManager)
	{
		sf::RenderWindow* window = gameManager->GetWindow();
		if (window)
		{
			window->setView(mView);
		}
	}
	if (mPlayer->getPosition().y >= GetWindowHeight())
	{
		mPlayer->SwitchFall();
	}
	mPlayer->Fall(GetDeltaTime());

	if (mPlayer->isMoving)
	{
		mPlayer->Decelerate(GetDeltaTime());
	}
}