#pragma once
#include "../LevelScene.h"

class Level4 : public LevelScene
{
protected:

	virtual void setNameLevel() override;
	virtual void editEntitiesCreated() override;
	virtual void goToNextLevel() override;
};

