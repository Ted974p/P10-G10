#include "RectangleCollider.h"
#include "CircleCollider.h"
#include <cmath>

RectangleCollider::RectangleCollider(sf::Vector2f _position, sf::Vector2f _size)
    : mPosition(_position), mSize(_size)
{
    mShapeTag = ShapeTag::Rectangle;
}

sf::Vector2f RectangleCollider::getPosition(float _ratioX, float _ratioY) const
{
    return mPosition + sf::Vector2f(mSize.x * _ratioX, mSize.y * _ratioY);
}

int RectangleCollider::isColliding(Collider* _other)
{
    switch (_other->getShapeTag())
    {
    case ShapeTag::Circle:
    {
        CircleCollider* otherCast = dynamic_cast<CircleCollider*>(_other);
        return circleRectangleCollision(otherCast, this);;
    }
    case ShapeTag::Rectangle:
    {
        RectangleCollider* otherCast = dynamic_cast<RectangleCollider*>(_other);
        return rectangleCollision(this, otherCast);;
    }
    }
    return false;
}

void RectangleCollider::repulse(Collider* _other)
{
    switch (_other->getShapeTag())
    {
    case ShapeTag::Circle:
    {
        CircleCollider* otherCast = dynamic_cast<CircleCollider*>(_other);
        circleRectangleRepulsion(otherCast, this);
        return;
    }
    case ShapeTag::Rectangle:
    {
        RectangleCollider* otherCast = dynamic_cast<RectangleCollider*>(_other);
        rectangleRepulsion(this, otherCast);
        return;
    }
    }
    return;
}

void RectangleCollider::setPosition(sf::Vector2f _position, float _ratioX, float _ratioY)
{
    mPosition = _position - sf::Vector2f(mSize.x * _ratioX, mSize.y * _ratioY);
}

void RectangleCollider::move(sf::Vector2f _delta)
{
    mPosition += _delta;
}