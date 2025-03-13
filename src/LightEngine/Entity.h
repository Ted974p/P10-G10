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
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;

    bool mIsRigidBody = false;
    bool mIsKinetic = false;

public:
	bool goToDirection(int x, int y, float speed = -1.f);
    bool goToPosition(int x, int y, float speed = -1.f);
	void setDirection(float x, float y, float speed = -1.f);
    void setSpeed(float speed) { mSpeed = speed; };
    void setTag(int tag) { mTag = tag; };
    void setRigidBody(bool _isRigitBody) { mIsRigidBody = _isRigitBody; }
    void setKinetic(bool _isKinetic) { mIsKinetic = _isKinetic; }
    
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
    T* createEntity(float radius, const sf::Color& color);

    void addCollider(CircleCollider* _collider);
    void addCollider(RectangleCollider* _collider);

    // Rendering
    void showGizmos();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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