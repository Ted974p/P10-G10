#pragma once

#include "Collider.h"

class RectangleCollider : public Collider
{
private:
    sf::RectangleShape* mShape; // for rendering (debug)

protected:
    sf::Vector2f mPosition;
    sf::Vector2f mSize;

public:
    RectangleCollider(Entity* _entity, sf::Vector2f _position, sf::Vector2f _size);
    ~RectangleCollider() = default;

    void move(sf::Vector2f _delta);

    // Accesseurs
    sf::Vector2f getPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const;
    sf::Vector2f getSize() const { return mSize; };

    void setPosition(sf::Vector2f _position, float _ratioX = 0.5f, float _ratioY = 0.5f);
    void setSize(sf::Vector2f _size) { mSize = _size; };

    // Collision
    int isColliding(Collider* _other) override;
    void repulse(Collider* _other) override;

    // Rendering
    virtual void showGizmos() override;
};
