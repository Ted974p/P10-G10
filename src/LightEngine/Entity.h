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

	std::vector<Collider*> mColliders;
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

    float mGravityAcceleration = 8.81f;
    float mMaxGravitySpeed = 30.0f;
    bool mAffect = false;
    bool mFalling = false;

public:
	bool goToDirection(int x, int y, float speed = -1.f);
    bool goToPosition(int x, int y, float speed = -1.f);
	void setDirection(float x, float y, float speed = -1.f);
    void setSpeed(float speed) { mSpeed = speed; };
    void setTag(int tag) { mTag = tag; };
    void setRigidBody(bool _isRigitBody) { mIsRigidBody = _isRigitBody; }
    void setKinetic(bool _isKinetic) { mIsKinetic = _isKinetic; }

    void SetEntityAffect(bool affect) { mAffect = affect; }
    void SetFalling(bool fall) { mFalling = fall; }
    void Falling(int DeltaTime);
    bool isAffect(bool affect) { return mAffect == affect; }
    bool isFalling(bool falling) { return mFalling == falling; }
    
    bool isRigidBody() const { return mIsRigidBody; }
    bool isKinetic() const { return mIsKinetic; }
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
    T* createEntity();

    void addCollider(CircleCollider* _collider);
    void addCollider(RectangleCollider* _collider);

    // Rendering
    void showGizmos();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:

    Entity() = default;
    ~Entity() = default;

    virtual void onUpdate() {};
    virtual void onInitialize() {};
	virtual void onDestroy() {};
	
private:

    void update();
	void initialize();

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"