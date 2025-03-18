#pragma once

#include "../Entity.h"
#include "PlayerEntity.h"


class LiftableEntity : public Entity
{
private:
	PlayerEntity* mPlayerLifting;

public:

	virtual void onInitialize() override;
	virtual void onDownCollision(Entity* _other) override;
	PlayerEntity* GetPlayerLifting() { return mPlayerLifting; }
	void setPlayerLifting(PlayerEntity* playerlifting) { mPlayerLifting = playerlifting; }
	virtual void onColliding(Entity* _other);
	virtual void onUpdate() override;
	//virtual void checkIfGrounded();
};

