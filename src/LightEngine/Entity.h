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
class SpriteSheet;
class Animator;

class Entity : public sf::Transformable, public sf::Drawable
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:

    SpriteSheet* mSpriteSheet;
    Animator* mAnimator;

	Collider* mCollider;
	sf::Vector2f mDirection;
    sf::Vector2f mForce;
	Target mTarget;
    float mSpeed = 0.2f;
    float mAcceleration = 5.f;
    float mMaxSpeed = 20.f;
    float mDeceleration = 5.0f;
    bool mToDestroy = false;
    int mTag = -1;
    bool mIsRigidBody = false;
    bool mIsKinetic = false;
    bool mIsGrounded = false;
    bool mHasGravity = true;

    float mMass = 10;
    float mGravityForce = 9.8f;

public:

    enum TAG
    {
        Player,
        Obstacle,
        Plateform,

        Count,
    };


	bool goToDirection(int x, int y, float speed = -1.f);
    bool goToPosition(int x, int y, float speed = -1.f);
	void setDirection(float x, float y, float speed = -1.f);
    void setSpeed(float speed) { mSpeed = speed; };
    void setTag(int tag) { mTag = tag; };
    void setRigidBody(bool _isRigitBody) { mIsRigidBody = _isRigitBody; }
    void setKinetic(bool _isKinetic) { mIsKinetic = _isKinetic; }
    void setMass(float _mass) { mMass = _mass; };
    void addForce(sf::Vector2f _force) { mForce += _force; };
    
    bool isRigidBody() const { return mIsRigidBody; }
    bool isKinetic() const { return mIsKinetic; }
    Collider* getCollider() const { return mCollider; };

	bool isTag(int tag) const { return mTag == tag; }
    void destroy();
	bool toDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* getScene() const;

    Scene* getScene() const;
	float getDeltaTime() const;
    float getMass() const { return mMass; };

    template<typename T>
    T* createEntity();

    void setCollider(CircleCollider* _collider);
    void setCollider(RectangleCollider* _collider);

    // Rendering
    void showGizmos();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:

    Entity() = default;
    ~Entity() = default;

    virtual void onUpCollision(Entity* _other) {};
    virtual void onDownCollision(Entity* _other) {};
    virtual void onLeftCollision(Entity* _other) {};
    virtual void onRightCollision(Entity* _other) {};

    virtual void onColliding(Entity* _other) {};
    virtual void onUpdate() {};
    virtual void onInitialize() {};
	virtual void onDestroy() {};
	
private:

    void applyGravity(float _dt);
    bool processCollision(Entity* other);
    void update();
	void initialize();

    friend class GameManager;
    friend Scene;
    friend class PlayerEntity;
};

#include "Entity.inl"