#pragma once
#include "../Entity.h"

class PlayerBody : public Entity
{
	bool isMovingRight;
	bool isMovingLeft;
	float mJumpForce = 12;

	bool isInLightEntity = false;
	sf::Clock lightTimer;
	bool speedBoostActive = false;

	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

public :

	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	void setInLightEntity(bool value);
	virtual void onUpdate() override;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
private:

	virtual void onDownCollision(Entity* other);
	virtual void checkIfGrounded();
};

