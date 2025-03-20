#pragma once

#include "../Scene.h"

class PlayerEntity;
class ObstacleEntity;
class GroundEntity;
class MovingPlatform;
class ButtonEntity;
class LiftableEntity;
class DoorEntity;
class LightEntity;
class PlayerBody;
class PlayerHead;
class Camera;

struct Position {
	int x;
	int y;
};

class LvEditorScene : public Scene
{
private:

	sf::View mView;
	std::vector<char> mSight;
	std::vector<Position> mPositions;

public:
	Camera* mCamera;
	LightEntity* light;
	PlayerEntity* player;
	ObstacleEntity* obstacle;
	ButtonEntity* button;
	GroundEntity* ground;
	MovingPlatform* platform;
	LiftableEntity* box;


	DoorEntity* door;
	PlayerBody* body;
	PlayerHead* head;

	Camera* getCamera();
	void onInitialize() override;
	void onEvent(const sf::Event& event) override {};
	void onUpdate() override;
	void CreateLv(std::string name);
};

