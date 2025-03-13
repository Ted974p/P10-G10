#include "SampleScene.h"

#include "../Entities/DummyEntity.h"

#include "../Utils/Debug.h"

void SampleScene::onInitialize()
{
	pEntity1 = createEntity<DummyEntity>();
	pEntity1->setPosition(100, 100);
	pEntity1->setRigidBody(true);

	pEntity2 = createEntity<DummyEntity>();
	pEntity2->setPosition(500, 500);
	pEntity2->setRigidBody(true);
}

void SampleScene::onEvent(const sf::Event& event)
{
}

void SampleScene::onUpdate()
{
}