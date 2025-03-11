#include "SampleScene.h"

#include "DummyEntity.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	pEntity1 = createEntity<DummyEntity>(50, sf::Color::Red);
	pEntity1->setPosition(100, 100);

	pEntity2 = createEntity<DummyEntity>(50, sf::Color::Green);
	pEntity2->setPosition(200, 100);

	pEntity1->addCollider(new CircleCollider(pEntity1, sf::Vector2f(0, 0), 50));
	pEntity2->addCollider(new CircleCollider(pEntity1, sf::Vector2f(0, 0), 50));
}

void SampleScene::OnEvent(const sf::Event& event)
{

    // Déplacement de circle1 avec Z, Q, S, D
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
        pEntity1->move(sf::Vector2f(0, -1));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        pEntity1->move(sf::Vector2f(0, 1));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        pEntity1->move(sf::Vector2f(-1, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        pEntity1->move(sf::Vector2f(1, 0));

    // Déplacement de circle2 avec les flèches
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        pEntity2->move(sf::Vector2f(0, -1));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        pEntity2->move(sf::Vector2f(0, 1));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        pEntity2->move(sf::Vector2f(-1, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        pEntity2->move(sf::Vector2f(1, 0));
}

void SampleScene::OnUpdate()
{
}