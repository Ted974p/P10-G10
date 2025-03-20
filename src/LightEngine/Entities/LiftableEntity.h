#pragma once

#include "../Entity.h"
#include "PlayerEntity.h"


class LiftableEntity : public Entity
{
private:
	PlayerEntity* mPlayerLifting;
	RectangleCollider* mColliderCast;
	RectangleCollider* mGroundCheck;

public:

	virtual void onInitialize() override;
	virtual void onDownCollision(Entity* _other) override;
	PlayerEntity* GetPlayerLifting() { return mPlayerLifting; }
	void setPlayerLifting(PlayerEntity* playerlifting) { mPlayerLifting = playerlifting; }
	virtual void onCollision(Entity* _other) override;
	virtual void onUpdate() override;
};

