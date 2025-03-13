#include "SampleScene.h"

#include "DummyEntity.h"

#include "Utils/Debug.h"

void SampleScene::OnInitialize()
{
	pEntity1 = createEntity<DummyEntity>(100, sf::Color::Red);
	pEntity1->setPosition(100, 100);
	pEntity1->setRigidBody(true);

	pEntity2 = createEntity<DummyEntity>(50, sf::Color::Green);
	pEntity2->setPosition(500, 500);
	pEntity2->setRigidBody(true);
}


void SampleScene::OnEvent(const sf::Event& event)
{
}

void SampleScene::OnUpdate()
{
}