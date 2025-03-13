#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;
class Collider;
class CircleCollider;
class RectangleCollider;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:

	std::vector<Collider*> mColliders;
    sf::Vector2f mPosition;
	sf::Vector2f mDirection;
	Target mTarget;
    float mSpeed = 0.2f;
    float mAcceleration = 5.f;
    float mMaxSpeed = 20.f;
    float mDeceleration = 5.0f;
    bool mToDestroy = false;
    int mTag = -1;
    bool mIsRigidBody = false;
    bool mIsKinetic = false;
    float mGravitySpeed = 8.2f;
    bool isFalling = false;
    float mGravityAcceleration = 8.81f;

public:
	bool goToDirection(int x, int y, float speed = -1.f);
    bool goToPosition(int x, int y, float speed = -1.f);
    void move(sf::Vector2f _delta) { mPosition += _delta; };
    void setPosition(float x, float y) { mPosition = sf::Vector2f(x, y); };
    void setPosition(sf::Vector2f _position) { mPosition = _position; };
	void setDirection(float x, float y, float speed = -1.f);
    void setSpeed(float speed) { mSpeed = speed; };
    void setTag(int tag) { mTag = tag; };
    void setRigidBody(bool _isRigitBody) { mIsRigidBody = _isRigitBody; }
    void setKinetic(bool _isKinetic) { mIsKinetic = _isKinetic; }
    
    bool isRigidBody() const { return mIsRigidBody; }
    bool isKinetic() const { return mIsKinetic; }
    sf::Vector2f getPosition() const { return mPosition; };
    std::vector<Collider*> getColliders() const { return mColliders; };

	bool isTag(int tag) const { return mTag == tag; }
    bool processCollision(Entity* other) const;

    void destroy();
	bool toDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* getScene() const;

    Scene* getScene() const;
	float getDeltaTime() const;

    template<typename T>
    T* createEntity(float radius, const sf::Color& color);

    void addCollider(CircleCollider* _collider);
    void addCollider(RectangleCollider* _collider);

    // Rendering
    void showGizmos();

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void onDestroy() {};
	
private:
    void update();
	void initialize(const sf::Color& color);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"