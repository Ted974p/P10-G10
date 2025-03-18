#include "ButtonEntity.h"

#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

#include "../RectangleCollider.h"

#include "../Rendering/SpriteSheet.h"
#include "../Rendering/Animation.h"
#include "../Rendering/Animator.h"
#include "../Scenes/AnimationScene.h"

#include <iostream>

void ButtonEntity::onInitialize()
{
    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    setRigidBody(false);
    setKinetic(false);
}

void ButtonEntity::SetDoor(DoorEntity* doorEntity)
{
    door = doorEntity;
    door->setRigidBody(true);
}

void ButtonEntity::onColliding(Entity* other)
{
    if (other->isTag((int)Entity::TAG::Player)) {
        std::cout << "Player detected in collision!" << std::endl;
        door->goToPosition(600.f, 200.f, 50.f);  
        door->setRigidBody(false);
        closingStarted = false;  
    }
    if (other->isTag((int)Entity::TAG::Player)) {
        std::cout << "Player left the button!" << std::endl;
        if (!closingStarted) {
            closingStarted = true;
            closingTimer.restart(); 
        }
    }
    else {
        std::cout << "This is not the player!" << std::endl;
    }
}

void ButtonEntity::onUpdate()
{
    if (closingStarted && closingTimer.getElapsedTime().asSeconds() >= DOOR_CLOSE_DELAY) {
        std::cout << "Closing the door!" << std::endl;
        door->goToPosition(600.f, 400.f, 50.f);  
        closingStarted = false;  
    }
}
