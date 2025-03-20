#pragma once
#include <SFML/Graphics.hpp>
#include "vector"

enum class ShapeTag 
{
	Circle,
	Rectangle,

	Count
};

class Entity;
class CircleCollider;
class RectangleCollider;

class Collider
{
protected:
	Entity* mEntity;
	ShapeTag mShapeTag;

	float distance(const sf::Vector2f& _p1, const sf::Vector2f& _p2);
	
	// Circle / Circle

	bool circleCollision(CircleCollider* _circle1, CircleCollider* _circle2);
	void circleRepulsion(CircleCollider* _circle1, CircleCollider* _circle2);

	// Rectangle / Rectangle
	
	bool rectangleCollision(RectangleCollider* _rect1, RectangleCollider* _rect2);
	void rectangleRepulsion(RectangleCollider* _rect1, RectangleCollider* _rect2);

	// Circle / Rectangle

	bool circleRectangleCollision(CircleCollider* circle, RectangleCollider* rect);
	void circleRectangleRepulsion(CircleCollider* _circle, RectangleCollider* _rect);

	bool isShapeTag(ShapeTag _tag) const { return mShapeTag == _tag; };


public:

	Collider(Entity* _entity);

	ShapeTag getShapeTag() const { return mShapeTag; };
	Entity* getEntity() const { return mEntity; };

	int getCollisionSide(Collider* _other);
	virtual void setPosition(sf::Vector2f _pos, float _ratioX = 0.5f, float _ratioY = 0.5f) = 0;
	virtual void move(sf::Vector2f _direction) = 0;
	virtual sf::Vector2f getPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const = 0;
	virtual int isColliding(Collider* _other) = 0;
	virtual void repulse(Collider* _other) = 0;
	virtual void showGizmos() = 0;
	virtual void onColliding() {};
};