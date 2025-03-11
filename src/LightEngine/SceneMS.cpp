#include "SceneMS.h"

#include "DummyEntity.h"

#include "Debug.h"

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
		mPlayer->MoveRight(1);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{

	}
}

void SceneMS::OnUpdate()
{
	
}