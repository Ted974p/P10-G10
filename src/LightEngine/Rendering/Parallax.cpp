#include "Parallax.h"
#include "../Managers/GameManager.h"
#include "../Entities/PlayerEntity.h"
#include "../RectangleCollider.h"
#include "Background.h"

void Parallax::addBackground(Background* _background)
{
    mBackgrounds.push_back(_background);
}

void Parallax::setPlayer(PlayerEntity* _player)
{
    mPlayer = _player;
    mColliderPlayer = dynamic_cast<RectangleCollider*>(_player->getCollider());
}

void Parallax::setReferencePoint(const sf::Vector2f& _point)
{
    mReferencePoint = _point;
}

void Parallax::update()
{
    if (!mPlayer) return;

    // Calcul du vecteur directionnel
    sf::Vector2f direction = mPlayer->getPosition() + mColliderPlayer->getSize() * 0.5f - mReferencePoint;

    for (Background* background : mBackgrounds)
    {
        float backgroundSpeed = background->getSpeed();
        sf::Vector2f uvOffset = direction * backgroundSpeed * 0.05f;
        background->updateUV(uvOffset.x, 0);
    }
}

void Parallax::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
    for (Background* background : mBackgrounds) {
        _target.draw(*background, _states);
    }
}