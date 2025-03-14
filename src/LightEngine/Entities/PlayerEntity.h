#pragma once
#include "../Entity.h"

class PlayerEntity : public Entity
{

private: 

	bool isMovingRight;
	bool isMovingLeft;

public:

	virtual void onInitialize() override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Decelerate(float deltaTime);
	virtual void onUpdate() override;
};

