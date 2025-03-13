#include "SceneMS.h"

#include "DummyEntity.h"

#include "Debug.h"
<<<<<<< Updated upstream

void SceneMS::OnInitialize()
{
=======
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

void SceneMS::OnInitialize()
{
	std::cout << "test";
	pEntity1 = CreateEntity<Entity>(50, sf::Color::Green);
	pEntity1->SetPosition(300, 300);
>>>>>>> Stashed changes

	mPlayer = CreateEntity<Player>(50, sf::Color::Blue);
	mPlayer->SetPosition(500, 500);
	mPlayer->SetRigidBody(true);

}

void SceneMS::OnEvent(const sf::Event& event)
{
<<<<<<< Updated upstream



=======
	
>>>>>>> Stashed changes
	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		mPlayer->MoveRight(GetDeltaTime());
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		mPlayer->SwitchFall();

	}


}

void SceneMS::OnUpdate()
{
	if (mPlayer->GetPosition().y >= GetWindowHeight())
	{
		mPlayer->SwitchFall();
	}
	mPlayer->Fall(GetDeltaTime());
}