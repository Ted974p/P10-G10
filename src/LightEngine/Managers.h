#pragma once

#pragma region Local Dependencies

#include "Managers/GameManager.h"
#include "Managers/InputManager.h"
#include "Managers/ResourceManager.h"

#pragma endregion

class Managers {
private:

	static Managers* m_instance;

	GameManager* m_gameManager;
	InputManager* m_inputManager;
	ResourceManager* m_resourceManager;

	Managers();

public:
	
	~Managers();

	GameManager* GetGameManager();
	InputManager* GetInputManager();
	ResourceManager* GetResourceManager();

	static Managers* GetInstance();
};