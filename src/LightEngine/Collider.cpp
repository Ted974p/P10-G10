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
    sf::Vector2f pos1 = _circle1->getPosition(0.5f, 0.5f);
    sf::Vector2f pos2 = _circle2->getPosition(0.5f, 0.5f);
    float rad1 = _circle1->getRadius();
    float rad2 = _circle2->getRadius();

    sf::Vector2f direction = pos1 - pos2;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0.0f)
        return;

    float totalOverlap = rad1 + rad2 - length;
    if (totalOverlap < 0.1f)
        return;

    direction /= length;

    const float damping = 0.8f;

    float ratio1 = _circle1->getEntity()->isKinetic()
        ? (_circle2->getEntity()->isKinetic() ? 0.5f : 1.0f)
        : (_circle2->getEntity()->isKinetic() ? 0.0f : 0.5f);
    float ratio2 = 1.0f - ratio1;

    _circle1->getEntity()->move(direction * totalOverlap * ratio1 * damping);
    _circle2->getEntity()->move(-direction * totalOverlap * ratio2 * damping);
}


// RECTANGLE / RECTANGLE

int Collider::getCollisionSide(Collider* _other)
{
    RectangleCollider* rect1 = dynamic_cast<RectangleCollider*>(this);
    RectangleCollider* rect2 = dynamic_cast<RectangleCollider*>(_other);

    if (rect1 == nullptr || rect2 == nullptr)
        return 0;

    // On récupère la position et la taille du premier rectangle
    sf::Vector2f rectPos = rect1->getPosition(0.0f, 0.0f);
    sf::Vector2f rectSize = rect1->getSize();

    // Calcul d'un point de contact moyen basé sur les centres des deux rectangles
    sf::Vector2f contactPoint = (rect1->getPosition(0.5f, 0.5f) + rect2->getPosition(0.5f, 0.5f)) * 0.5f;

    float leftDist = std::fabs(contactPoint.x - rectPos.x);
    float rightDist = std::fabs(contactPoint.x - (rectPos.x + rectSize.x));
    float topDist = std::fabs(contactPoint.y - rectPos.y);
    float bottomDist = std::fabs(contactPoint.y - (rectPos.y + rectSize.y));

    const float epsilon = 0.01f;

    if (std::min(leftDist, rightDist) <= std::min(topDist, bottomDist)) {
        if (leftDist < rightDist - epsilon)
            return 3;  // Gauche
        if (rightDist < leftDist + epsilon)
            return 2;  // Droite
    }

    if (topDist < bottomDist - epsilon)
        return 1;      // Haut
    if (bottomDist < topDist + epsilon)
        return 4;      // Bas

    return 0;
}


bool Collider::rectangleCollision(RectangleCollider* rect1, RectangleCollider* rect2)
{
    sf::Vector2f pos1 = rect1->getPosition(0, 0);
    sf::Vector2f size1 = rect1->getSize();
    sf::Vector2f pos2 = rect2->getPosition(0, 0);
    sf::Vector2f size2 = rect2->getSize();

    // Vérification de la superposition (collision)
    if (pos1.x <= pos2.x + size2.x &&
        pos1.x + size1.x >= pos2.x &&
        pos1.y <= pos2.y + size2.y &&
        pos1.y + size1.y >= pos2.y)
    {
        return true;
    }

    return false;
}

void Collider::rectangleRepulsion(RectangleCollider* _rect1, RectangleCollider* _rect2) {
    sf::Vector2f pos1 = _rect1->getPosition(0, 0);
    sf::Vector2f size1 = _rect1->getSize();
    sf::Vector2f pos2 = _rect2->getPosition(0, 0);
    sf::Vector2f size2 = _rect2->getSize();

    float right1 = pos1.x + size1.x;
    float bottom1 = pos1.y + size1.y;
    float right2 = pos2.x + size2.x;
    float bottom2 = pos2.y + size2.y;

    float intersectX = std::min(right1, right2) - std::max(pos1.x, pos2.x);
    float intersectY = std::min(bottom1, bottom2) - std::max(pos1.y, pos2.y);

    if (intersectX < 0.1f && intersectY < 0.1f)
        return;

    float ratio1 = _rect1->getEntity()->isKinetic()
        ? (_rect2->getEntity()->isKinetic() ? 0.5f : 1.0f)
        : (_rect2->getEntity()->isKinetic() ? 0.0f : 0.5f);
    float ratio2 = 1.0f - ratio1;

    const float damping = 1.0f;

    if (intersectX > 0 && intersectY > 0) {
        sf::Vector2f moveVector;

        if (intersectX < intersectY) {
            moveVector.x = (pos2.x > pos1.x) ? -intersectX : intersectX;
            moveVector.y = 0;
        }
        else {
            moveVector.x = 0;
            moveVector.y = (pos2.y > pos1.y) ? -intersectY : intersectY;
        }

        _rect1->getEntity()->move(moveVector * ratio1 * damping);
        _rect2->getEntity()->move(-moveVector * ratio2 * damping);
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
        return true;

    return false;
}

void Collider::circleRectangleRepulsion(CircleCollider* _circle, RectangleCollider* _rect) {
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
    if (distanceSquared == 0.0f)
        return;

    float distance = std::sqrt(distanceSquared);
    float overlap = radius - distance;
    // Seuil minimal pour éviter des corrections trop faibles
    if (overlap < 0.1f)
        return;

    repulsionVector /= distance;

    // Facteur d'amortissement
    const float damping = 0.8f;

    float ratioRect = _rect->getEntity()->isKinetic()
        ? (_circle->getEntity()->isKinetic() ? 0.5f : 1.0f)
        : (_circle->getEntity()->isKinetic() ? 0.0f : 0.5f);
    float ratioCircle = 1.0f - ratioRect;

    _circle->getEntity()->move(repulsionVector * overlap * ratioCircle * damping);
    _rect->getEntity()->move(-repulsionVector * overlap * ratioRect * damping);
}

