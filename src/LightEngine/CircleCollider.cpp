#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Entity.h"
#include "Debug.h"

CircleCollider::CircleCollider(Entity* _entity, sf::Vector2f _position, float _radius)
	: Collider(_entity), mPosition(_position), mRadius(_radius)
{
	mShapeTag = ShapeTag::Circle;
    mShape = new sf::CircleShape(_radius);
    mShape->setPosition(_position);
}

sf::Vector2f CircleCollider::getPosition(float _ratioX, float _ratioY) const
{
    return mEntity->getPosition() + mPosition + sf::Vector2f(mRadius * 2 * _ratioX, mRadius * 2 * _ratioY);
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

void CircleCollider::showGizmos()
{
    sf::Vector2f position = getPosition();
    Debug::DrawCircle(position.x, position.y, mRadius, sf::Color::Green);
}