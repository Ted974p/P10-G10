#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <unordered_map>

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
    // Components
    SpriteSheet* mSpriteSheet;
    Animator* mAnimator;
    Animator* mAnimator2;
    Collider* mCollider;

    // Movement & Physics
    sf::Vector2f mDirection;
    sf::Vector2f mForce = sf::Vector2f(0, 0);
    Target mTarget;
    float mSpeed = 0.2f;
    float mAcceleration = 5.f;
    float mMaxSpeed = 20.f;
    float mDeceleration = 5.0f;
    float mMass = 10;
    float mGravityForce = 9.8f;
    bool mIsRigidBody = false;
    bool mIsKinetic = false;
    bool mIsGrounded = false;

    // Collision
    std::unordered_map<Entity*, bool> mIsColliding;
    int mLastCollisionSide = 0;
    bool mIsEnter = false;
    bool mIsExit = false;

    // State
    bool mToDestroy = false;
    int mTag = -1;

public:
    enum TAG
    {
        Player,
        Obstacle,
        Plateform,
        MovingPlatform,
        Head,
        Button,
        Count,
    };

    // Movement
    bool goToDirection(int x, int y, float speed = -1.f);
    bool goToPosition(int x, int y, float speed = -1.f);
    void setDirection(float x, float y, float speed = -1.f);
    void addForce(sf::Vector2f _force) { mForce += _force; }

    // Setters
    void setSpeed(float speed) { mSpeed = speed; }
    void setTag(int tag) { mTag = tag; }
    void setRigidBody(bool _isRigidBody) { mIsRigidBody = _isRigidBody; }
    void setKinetic(bool _isKinetic) { mIsKinetic = _isKinetic; }
    void setMass(float _mass) { mMass = _mass; }
    void setCollider(CircleCollider* _collider);
    void setCollider(RectangleCollider* _collider);

    // Getters
    bool isRigidBody() const { return mIsRigidBody; }
    bool isKinetic() const { return mIsKinetic; }
    Collider* getCollider() const { return mCollider; }
    bool isTag(int tag) const { return mTag == tag; }
    float getMass() const { return mMass; }
    bool toDestroy() const { return mToDestroy; }
    float getDeltaTime() const;

    template<typename T>
    T* getScene() const;
    Scene* getScene() const;

    template<typename T>
    T* createEntity();

    // Collision Events
    virtual void onUpCollisionEnter(Entity* other) { mIsEnter = false; }
    virtual void onDownCollisionEnter(Entity* other) { mIsEnter = false; }
    virtual void onLeftCollisionEnter(Entity* other) { mIsEnter = false; }
    virtual void onRightCollisionEnter(Entity* other) { mIsEnter = false; }

    virtual void onUpCollision(Entity* other) {}
    virtual void onDownCollision(Entity* other) { mIsGrounded = true; }
    virtual void onLeftCollision(Entity* other) {}
    virtual void onRightCollision(Entity* other) {}

    virtual void onUpCollisionExit(Entity* other) { mIsExit = false; }
    virtual void onDownCollisionExit(Entity* other) { mIsExit = false; }
    virtual void onLeftCollisionExit(Entity* other) { mIsExit = false; }
    virtual void onRightCollisionExit(Entity* other) { mIsExit = false; }

    virtual void onCollisionEnter(Entity* other) { mIsEnter = true; }
    virtual void onCollision(Entity* other) {}
    virtual void onCollisionExit(Entity* other) { mIsExit = true; }

    // Lifecycle Methods
    virtual void onUpdate() {}
    virtual void onInitialize() {}
    virtual void onDestroy() {}
    void destroy();

    // Rendering
    void showGizmos();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    Entity() = default;
    ~Entity() = default;

private:
    // Physics
    void updatePhysics(float deltaTime);
    void applyGravity(float _dt);
    void applyRepulsion(Entity* other);
    void applySideCollisions(Entity* other);
    bool detectCollision(Entity* other);

    // Internal Updates
    void update();
    void initialize();

    friend class GameManager;
    friend Scene;
    friend class PlayerEntity;
};

#include "Entity.inl"