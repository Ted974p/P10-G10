#pragma once

#include <string>
#include <vector>
#include "../Scene.h"


class Camera;
class PlayerEntity;
class ButtonEntity;
class DoorEntity;
class TargetEntity;
class ActivablePlatform;

struct Position {
	int x;
	int y;
};

class LevelScene : public Scene
{
private:

	std::vector<char> mSight;
	std::vector<Position> mPositions;

protected:
	std::string mNameLevel;
	Camera* mCamera;
	PlayerEntity* mPlayer;

	std::vector<ButtonEntity*> buttons;
	std::vector<DoorEntity*> doors;
	std::vector<ActivablePlatform*> platforms;

public:

	Camera* getCamera();
	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override;

protected:

	virtual void editEntitiesCreated() = 0;
	virtual void setNameLevel() = 0;

private:

	void createLv(std::string name);
};

