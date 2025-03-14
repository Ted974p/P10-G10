#include "PhysicsScene.h"

#include "../Entities/DummyEntity.h"

#include "../CircleCollider.h"
#include "../RectangleCollider.h"

#include "../Utils/Debug.h"

#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include <iostream>

void PhysicsScene::onInitialize()
{
	pEntity1 = createEntity<DummyEntity>();
	pEntity1->setPosition(100, 100);

	pEntity2 = createEntity<DummyEntity>();
	pEntity2->setPosition(200, 100);

	//pEntity1->addCollider(new CircleCollider(pEntity1, sf::Vector2f(0, 0), 50));
	//pEntity2->addCollider(new CircleCollider(pEntity2, sf::Vector2f(0, 0), 50));

    pEntity1->setCollider(new RectangleCollider(pEntity1, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    pEntity2->setCollider(new RectangleCollider(pEntity2, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));

    pEntity1->setRigidBody(true);
    pEntity2->setRigidBody(true);

    pEntity1->setKinetic(true);
    pEntity2->setKinetic(true);

    // EXEMPLE CREATION DU SOL

    DummyEntity* ground = createEntity<DummyEntity>();
    ground->setPosition(0, 700);
    ground->setCollider(new RectangleCollider(ground, sf::Vector2f(0, 0), sf::Vector2f(1280, 100)));
    ground->setRigidBody(true);
    ground->setKinetic(false);
}

void PhysicsScene::onEvent(const sf::Event& event)
{

    float horizontal1 = inputManager->GetAxis("Horizontal");
    float vertical1 = inputManager->GetAxis("Vertical");

    sf::Vector2f direction1(horizontal1, vertical1);

    pEntity1->move(direction1);

    float horizontal2 = inputManager->GetAxis("HorizontalArrows");
    float vertical2 = inputManager->GetAxis("VerticalArrows");

    sf::Vector2f direction2(horizontal2, vertical2);

    pEntity2->move(direction2);
}