#include "MovingPlatform.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/GameManager.h"
#include "../Rendering/SpriteSheet.h"

#include <iostream>
#include <cmath>

void MovingPlatform::onInitialize()
{
    movingStarted = false;
    startPosition = getPosition();

    setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(64, 64)));
    setRigidBody(true);
    setKinetic(false); 
    setTag(int(Entity::TAG::MovingPlatform)); 

    sf::Texture* texture1 = resourceManager->GetTexture("props");
    if (!texture1) {
        std::cerr << "Erreur : Impossible de charger la texture 'props'." << std::endl;
    }
    mSpriteSheet = new SpriteSheet(texture1, 4, 6);
    mSpriteSheet->setPosition(32, -12); 
    mSpriteSheet->setScale(0.64f, 0.64f); 
    mSpriteSheet->setCurrent(5); 

    // filoutage pour camoufler les problèmes de spritesheet
    sf::Vector2f hv = mSpriteSheet->getHV();
    sf::Vector2f xy = mSpriteSheet->getXY();
    mSpriteSheet->setTextureRect(sf::IntRect(xy.x * hv.x, xy.y * hv.y + 3, hv.x, hv.y));

    direction = sf::Vector2f(0, 0);
}

void MovingPlatform::onUpdate() {

    if (!isActive)
        return;

    if (!movingStarted) {
        movingTimer.restart();
        movingStarted = true;
        startPosition = getPosition();
    }

    if (mIsStopped && !loopMovement) {
        return;
    }

    float deltaTime = gameManager->GetDeltaTime();
    sf::Vector2f currentPosition = getPosition();

    float distanceFromStartX = currentPosition.x - startPosition.x;
    float distanceFromStartY = currentPosition.y - startPosition.y;

    if (std::abs(distanceFromStartX) >= maxDistance || std::abs(distanceFromStartY) >= maxDistance) {
        direction = -direction;
        startPosition = getPosition(); 

        if (loopMovement) {
            return;
        }

        if (mHasReturnedToStart) {
            mIsStopped = true;
            direction = sf::Vector2f(0.f, 0.f);
            setPosition(startPosition);
        }
        else {
            mHasReturnedToStart = true;
        }
    }

    move(direction * mSpeed * deltaTime);
}


