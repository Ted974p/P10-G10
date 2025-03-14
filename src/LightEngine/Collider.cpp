#include "Collider.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Utils/Utils.h"
#include "Entity.h"

#include <iostream>

Collider::Collider(Entity* _entity) {
    mShapeTag = ShapeTag::Count;
    mEntity = _entity;
}

float Collider::distance(const sf::Vector2f& _p1, const sf::Vector2f& _p2) {
    return sqrt((_p1.x - _p2.x) * (_p1.x - _p2.x) + (_p1.y - _p2.y) * (_p1.y - _p2.y));
}

// CIRCLE / CIRCLE

bool Collider::circleCollision(CircleCollider* _circle1, CircleCollider* _circle2) {
    sf::Vector2f pos1 = _circle1->getPosition(0.5f, 0.5f);
    float rad1 = _circle1->getRadius();
    sf::Vector2f pos2 = _circle2->getPosition(0.5f, 0.5f);
    float rad2 = _circle2->getRadius();

    return distance(pos1, pos2) < (rad1 + rad2);
}

void Collider::circleRepulsion(CircleCollider* _circle1, CircleCollider* _circle2) {
    if (!circleCollision(_circle1, _circle2)) return;

    sf::Vector2f pos1 = _circle1->getPosition(0.5f, 0.5f);
    sf::Vector2f pos2 = _circle2->getPosition(0.5f, 0.5f);
    float rad1 = _circle1->getRadius();
    float rad2 = _circle2->getRadius();

    sf::Vector2f direction = pos1 - pos2;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0.0f) return;  // Évite la division par zéro

    float totalOverlap = rad1 + rad2 - length;
    direction /= length;

    float ratio1 = _circle1->getEntity()->isKinetic() ? (_circle2->getEntity()->isKinetic() ? 0.5f : 1.0f) : (_circle2->getEntity()->isKinetic() ? 0.0f : 0.5f);
    float ratio2 = 1.0f - ratio1;

    _circle1->getEntity()->move(direction * totalOverlap * ratio1);
    _circle2->getEntity()->move(-direction * totalOverlap * ratio2);
}

// RECTANGLE / RECTANGLE

int Collider::getCollisionSide(RectangleCollider* _rect, sf::Vector2f point) {
    sf::Vector2f rectPos = _rect->getPosition(0.0f, 0.0f);
    sf::Vector2f rectSize = _rect->getSize();

    float leftDist = Utils::lenghtSquared((rectPos + sf::Vector2f(0, rectSize.y / 2)) - point);
    float rightDist = Utils::lenghtSquared((rectPos + sf::Vector2f(rectSize.x, rectSize.y / 2)) - point);
    float topDist = Utils::lenghtSquared((rectPos + sf::Vector2f(rectSize.x / 2, 0)) - point);
    float bottomDist = Utils::lenghtSquared((rectPos + sf::Vector2f(rectSize.x / 2, rectSize.y)) - point);

    float minDist = std::min({ leftDist, rightDist, topDist, bottomDist });

    if (minDist == topDist)    return 1;  // Haut
    if (minDist == rightDist)  return 2;  // Droite
    if (minDist == bottomDist) return 3;  // Bas
    if (minDist == leftDist)   return 4;  // Gauche
}

int Collider::rectangleCollision(RectangleCollider* _rect1, RectangleCollider* _rect2) {
    sf::Vector2f pos1 = _rect1->getPosition(0, 0);
    sf::Vector2f size1 = _rect1->getSize();
    sf::Vector2f pos2 = _rect2->getPosition(0, 0);
    std::cout << pos2.x << " , " << pos2.y << std::endl;
    sf::Vector2f size2 = _rect2->getSize();

    if (pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x &&
        pos1.y < pos2.y + size2.y && pos1.y + size1.y > pos2.y)
        return getCollisionSide(_rect2, _rect1->getPosition(0.5f, 0.5f));

    return 0;
}

void Collider::rectangleRepulsion(RectangleCollider* _rect1, RectangleCollider* _rect2) {
    if (!rectangleCollision(_rect1, _rect2)) return;

    sf::Vector2f pos1 = _rect1->getPosition(0, 0);
    sf::Vector2f size1 = _rect1->getSize();
    sf::Vector2f pos2 = _rect2->getPosition(0, 0);
    sf::Vector2f size2 = _rect2->getSize();

    float deltaX = pos2.x - pos1.x;
    float deltaY = pos2.y - pos1.y;
    float intersectX = (size1.x + size2.x) / 2 - std::abs(deltaX);
    float intersectY = (size1.y + size2.y) / 2 - std::abs(deltaY);

    if (intersectX > 0 && intersectY > 0) {
        sf::Vector2f moveVector;
        if (intersectX < intersectY) {
            moveVector.x = (deltaX > 0) ? -intersectX : intersectX;
        }
        else {
            moveVector.y = (deltaY > 0) ? -intersectY : intersectY;
        }

        float ratio1 = _rect1->getEntity()->isKinetic() ? (_rect2->getEntity()->isKinetic() ? 0.5f : 1.0f) : (_rect2->getEntity()->isKinetic() ? 0.0f : 0.5f);
        float ratio2 = 1.0f - ratio1;

        _rect1->getEntity()->move(moveVector * ratio1);
        _rect2->getEntity()->move(-moveVector * ratio2);
    }
}


// CIRCLE / RECTANGLE

bool Collider::circleRectangleCollision(CircleCollider* _circle, RectangleCollider* _rect) {
    sf::Vector2f circleCenter = _circle->getPosition(0.5f, 0.5f);
    float radius = _circle->getRadius();
    sf::Vector2f rectPos = _rect->getPosition(0, 0);
    sf::Vector2f rectSize = _rect->getSize();

    float closestX = std::max(rectPos.x, std::min(circleCenter.x, rectPos.x + rectSize.x));
    float closestY = std::max(rectPos.y, std::min(circleCenter.y, rectPos.y + rectSize.y));

    if (distance(circleCenter, { closestX, closestY }) <= radius)
        return getCollisionSide(_rect, _circle->getPosition(0.5f, 0.5f));

    return 0;
}

void Collider::circleRectangleRepulsion(CircleCollider* _circle, RectangleCollider* _rect) {
    if (!circleRectangleCollision(_circle, _rect)) return;

    sf::Vector2f circleCenter = _circle->getPosition(0.5f, 0.5f);
    float radius = _circle->getRadius();
    sf::Vector2f rectPos = _rect->getPosition(0, 0);
    sf::Vector2f rectSize = _rect->getSize();

    // Calcul du point le plus proche sur le rectangle
    float closestX = std::clamp(circleCenter.x, rectPos.x, rectPos.x + rectSize.x);
    float closestY = std::clamp(circleCenter.y, rectPos.y, rectPos.y + rectSize.y);
    sf::Vector2f closestPoint(closestX, closestY);

    // Calcul du vecteur de repulsion
    sf::Vector2f repulsionVector = circleCenter - closestPoint;
    float distanceSquared = repulsionVector.x * repulsionVector.x + repulsionVector.y * repulsionVector.y;

    if (distanceSquared == 0.0f) return;

    float distance = std::sqrt(distanceSquared);
    float overlap = radius - distance;

    if (overlap > 0) {
        repulsionVector /= distance;

        float ratioRect = _rect->getEntity()->isKinetic() ? (_circle->getEntity()->isKinetic() ? 0.5f : 1.0f) : (_circle->getEntity()->isKinetic() ? 0.0f : 0.5f);
        float ratioCircle = 1.0f - ratioRect;

        _circle->getEntity()->move(repulsionVector * overlap * ratioCircle);
        _rect->getEntity()->move(-repulsionVector * overlap * ratioRect);
    }
}
