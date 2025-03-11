#pragma once
#include <SFML/Graphics.hpp>
#include "vector"

enum class ShapeTag 
{
	Circle,
	Rectangle,

	Count
};

class CircleCollider;
class RectangleCollider;

class Collider 
{
protected:

	ShapeTag mShapeTag;
	bool mIsRigidBody = false;
	bool mIsKinetic = false;

	float distance(const sf::Vector2f& _p1, const sf::Vector2f& _p2);
	int getCollisionSide(RectangleCollider* _rect, sf::Vector2f point);

	// Circle / Circle

	bool circleCollision(CircleCollider* _circle1, CircleCollider* _circle2);
	void circleRepulsion(CircleCollider* _circle1, CircleCollider* _circle2);

	// Rectangle / Rectangle
	
	int rectangleCollision(RectangleCollider* _rect1, RectangleCollider* _rect2);
	void rectangleRepulsion(RectangleCollider* _rect1, RectangleCollider* _rect2);

	// Circle / Rectangle

	bool circleRectangleCollision(CircleCollider* circle, RectangleCollider* rect);
	void circleRectangleRepulsion(CircleCollider* _circle, RectangleCollider* _rect);

	bool isShapeTag(ShapeTag _tag) const { return mShapeTag == _tag; };


public:

	ShapeTag getShapeTag() const { return mShapeTag; };


	void setRigidBody(bool _isRigitBody) { mIsRigidBody = _isRigitBody; }
	void setKinetic(bool _isKinetic) { mIsKinetic = _isKinetic; }

	bool isRigidBody() const { return mIsRigidBody; }
	bool isKinetic() const { return mIsKinetic; }

	virtual void setPosition(sf::Vector2f _pos, float _ratioX = 0.5f, float _ratioY = 0.5f) = 0;
	virtual void move(sf::Vector2f _direction) = 0;
	virtual sf::Vector2f getPosition(float _ratioX = 0.5f, float _ratioY = 0.5f) const = 0;
	virtual int isColliding(Collider* _other) = 0;
	virtual void repulse(Collider* _other) = 0;
};