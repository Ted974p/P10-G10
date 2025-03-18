#pragma once

#include <list>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class Background;
class PlayerEntity;
class RectangleCollider;

class Parallax : public sf::Drawable
{
protected:
    std::list<Background*> mBackgrounds = {};
    PlayerEntity* mPlayer = nullptr;
    RectangleCollider* mColliderPlayer = nullptr;
    sf::Vector2f mReferencePoint = { 0.0f, 0.0f };

public:
    Parallax() = default;
    ~Parallax() = default;

    void addBackground(Background* _background);
    void setPlayer(PlayerEntity* _player);
    void setReferencePoint(const sf::Vector2f& _point);
    void update();
    virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
};