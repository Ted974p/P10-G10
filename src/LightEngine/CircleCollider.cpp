#include "CircleCollider.h"
#include "RectangleCollider.h"

#include "iostream"

CircleCollider::CircleCollider(sf::Vector2f _position, float _radius)
	: mPosition(_position), mRadius(_radius)
{
	mShapeTag = ShapeTag::Circle;
}

sf::Vector2f CircleCollider::getPosition(float _ratioX, float _ratioY) const
{
    return mPosition + sf::Vector2f(mRadius * 2 * _ratioX, mRadius * 2 * _ratioY);
}

void CircleCollider::setPosition(sf::Vector2f _position, float _ratioX, float _ratioY)
{
    mPosition = _position - sf::Vector2f(mRadius * 2 * _ratioX, mRadius * 2 * _ratioY);
}

void CircleCollider::move(sf::Vector2f _delta)
{
    mPosition += _delta;
}

int CircleCollider::isColliding(Collider* _other)
{
    switch (_other->getShapeTag())
    {
    case ShapeTag::Circle:
    {
        CircleCollider* otherCast = dynamic_cast<CircleCollider*>(_other);
        return circleCollision(this, otherCast);
    }
    case ShapeTag::Rectangle:
    {
        RectangleCollider* otherCast = dynamic_cast<RectangleCollider*>(_other);
        return circleRectangleCollision(this, otherCast);
    }
    }
    return false;
}

void CircleCollider::repulse(Collider* _other)
{
    switch (_other->getShapeTag())
    {
    case ShapeTag::Circle:
    {
        CircleCollider* otherCast = dynamic_cast<CircleCollider*>(_other);
        circleRepulsion(this, otherCast);
        return;
    }
    case ShapeTag::Rectangle:
    {
        RectangleCollider* otherCast = dynamic_cast<RectangleCollider*>(_other);
        circleRectangleRepulsion(this, otherCast);
        return;
    }
    }
}