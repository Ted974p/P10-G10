#pragma once

#include "../LevelScene.h"

class Level1 : public LevelScene
{
protected:

	virtual void setNameLevel() override;
	virtual void editEntitiesCreated() override;
	virtual void goToNextLevel() override;
};

