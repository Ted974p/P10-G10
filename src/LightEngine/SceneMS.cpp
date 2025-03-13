#include "SceneMS.h"

#include "DummyEntity.h"

#include "Utils/Debug.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

void SceneMS::OnInitialize()
{
	pEntity1 = createEntity<Entity>(50, sf::Color::Green);
	pEntity1->setPosition(300, 300);

	mPlayer = createEntity<Player>(50, sf::Color::Blue);
	mPlayer->setPosition(500, 500);
	mPlayer->setRigidBody(true);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == false)
	{
		mPlayer->Decelerate(GetDeltaTime());
	}


	// Met � jour la position de la vue en douceur
	sf::Vector2f targetPosition = mPlayer->getPosition();
	sf::Vector2f currentViewPosition = mView.getCenter();

	// Ajout d'une interpolation (lerp) pour lisser le mouvement
	float smoothFactor; // Ajuste selon tes besoins
	/*if (mPlayer->GetPosition().x < mView.getCenter().x - mView.getSize().x / 2 || mPlayer->GetPosition().x > mView.getCenter().x + mView.getSize().x / 2)
	{
		smoothFactor = 5.f * GetDeltaTime();
	}

	else
	{
		smoothFactor = 1.f * GetDeltaTime();
	}*/

	smoothFactor = 1.f * GetDeltaTime();

	mView.setCenter(currentViewPosition + (targetPosition - currentViewPosition) * smoothFactor);

	static GameManager* pGameManager = GameManager::GetInstance();;
	if (pGameManager)
	{
		sf::RenderWindow* window = pGameManager->GetWindow();
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
}