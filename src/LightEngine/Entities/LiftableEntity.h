#pragma once

#include "../Entity.h"
#include "PlayerEntity.h"


class LiftableEntity : public Entity
{
private:
	PlayerEntity* mPlayerLifting;

public:

	virtual void onInitialize() override;
	PlayerEntity* GetPlayerLifting() { return mPlayerLifting; }
	void setPlayerLifting(PlayerEntity* playerlifting) { mPlayerLifting = playerlifting; }
	virtual void onColliding(Entity* _other) override;
	virtual void onUpdate() override;
};

