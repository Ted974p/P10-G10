#include "Collider.h"

class CircleCollider : public Collider
{
protected:
    sf::Vector2f mPosition; // Centre du cercle
    float mRadius;

public:
    CircleCollider(sf::Vector2f _position, float _radius);
    ~CircleCollider() = default;

    void move(sf::Vector2f _delta);

    // Accesseurs
    sf::Vector2f getPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const;
    float getRadius() const { return mRadius; };

    void setPosition(sf::Vector2f _position, float _ratioX = 0.5f, float _ratioY = 0.5f);
    void setRadius(float _radius) { mRadius = _radius; };

    // Collision
    int isColliding(Collider* _other) override;
    void repulse(Collider* _other) override;
};