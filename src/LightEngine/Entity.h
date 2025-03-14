#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <vector>

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
    // Structure représentant la cible vers laquelle se déplace l'entité
    struct Target
    {
        sf::Vector2i position;
        float distance;
        bool isSet;
    };

private:
    // Parent de l'entité
    Entity* mParent = nullptr;
    // Liste des enfants de l'entité
    std::vector<Entity*> mChildrens;

protected:
    // Composants de l'entité
    SpriteSheet* mSpriteSheet;
    Animator* mAnimator;
    Collider* mCollider;

    // Propriétés de l'entité
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
    float mMass = 10;
    float mGravityForce = 9.8f;
    sf::Vector2f mLocalPosition;

public:
    // --------------------------------------
    // Gestion de la position et du mouvement
    // --------------------------------------

    bool goToDirection(int x, int y, float speed = -1.f);
    bool goToPosition(int x, int y, float speed = -1.f);
    void setDirection(float x, float y, float speed = -1.f);
    void setSpeed(float speed) { mSpeed = speed; };
    void setRelativePosition(const sf::Vector2f& position);
    void moveRelative(const sf::Vector2f& offset);

    // --------------------------------------
    // Gestion des forces et de la physique
    // --------------------------------------

    void addForce(sf::Vector2f _force) { mForce += _force; };
    void setMass(float _mass) { mMass = _mass; };
    void setRigidBody(bool _isRigitBody) { mIsRigidBody = _isRigitBody; }
    void setKinetic(bool _isKinetic) { mIsKinetic = _isKinetic; }
    void applyGravity(float _dt);

    // --------------------------------------
    // Gestion des collisions
    // --------------------------------------

    bool processCollision(Entity* other);
    void setCollider(CircleCollider* _collider);
    void setCollider(RectangleCollider* _collider);

    // --------------------------------------
    // Gestion du parent et des enfants
    // --------------------------------------

    void addChildren(Entity* _child);
    void removeChild(Entity* child);
    void removeAllChildren();
    void setParent(Entity* _parent) { mParent = _parent; };

    Entity* getParent() const { return mParent; }
    const std::vector<Entity*>& getChildren() const { return mChildrens; }

    // --------------------------------------
    // Méthodes utilitaires
    // --------------------------------------

    bool isRigidBody() const { return mIsRigidBody; }
    bool isKinetic() const { return mIsKinetic; }
    Collider* getCollider() const { return mCollider; };
    sf::Vector2f getLocalPosition() const { return mLocalPosition; }
    bool isTag(int tag) const { return mTag == tag; }
    float getMass() const { return mMass; };
    template<typename T> T* getScene() const;
    Scene* getScene() const;
    float getDeltaTime() const;
    void destroy();
    bool toDestroy() const { return mToDestroy; }

    template<typename T>
    T* createEntity();

    // --------------------------------------
    // Méthodes de rendu
    // --------------------------------------

    void showGizmos();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    // --------------------------------------
    // Méthodes d'initialisation et de mise à jour
    // --------------------------------------

    Entity() = default;
    ~Entity() = default;

    virtual void onUpCollision() {};
    virtual void onDownCollision() {};
    virtual void onLeftCollision() {};
    virtual void onRightCollision() {};

    virtual void onColliding() {};
    virtual void onUpdate() {};
    virtual void onInitialize() {};
    virtual void onDestroy() {};

private:

    // --------------------------------------
    // Méthodes internes
    // --------------------------------------

    void initialize();
    void update();
    void updateChildrens();

    friend class GameManager;
    friend Scene;
    friend class PlayerEntity;
};

#include "Entity.inl"
