#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "Entity.h"
#include "Utils/Debug.h"

RectangleCollider::RectangleCollider(Entity* _entity, sf::Vector2f _position, sf::Vector2f _size)
    : Collider(_entity), mPosition(_position), mSize(_size)
{
    mShapeTag = ShapeTag::Rectangle;
    mShape = new sf::RectangleShape(_size);
    mShape->setPosition(_position);
}

sf::Vector2f RectangleCollider::getPosition(float _ratioX, float _ratioY) const
{
    return mEntity->getPosition() + mPosition + sf::Vector2f(mSize.x * _ratioX, mSize.y * _ratioY);
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

void RectangleCollider::showGizmos()
{
    sf::Vector2f position = getPosition(0, 0);
    Debug::DrawRectangle(position.x, position.y, mSize.x, mSize.y, sf::Color::Green);
}