#include "Managers.h"
#include <iostream>

Managers* Managers::m_instance = nullptr;

Managers::Managers() {
	// DO STUFF AFTER OBJECT CREATION //

	m_gameManager = new GameManager();
	m_inputManager = new InputManager();
	m_resourceManager = new ResourceManager();
}

Managers::~Managers() {
	delete m_gameManager;
	delete m_inputManager;
	delete m_resourceManager;

	m_instance = nullptr;
}

GameManager* Managers::GetGameManager()
{
	return m_gameManager;
}

InputManager* Managers::GetInputManager()
{
	return m_inputManager;
}

ResourceManager* Managers::GetResourceManager()
{
	return m_resourceManager;
}

Managers* Managers::GetInstance() {
	if (m_instance == nullptr) {
		m_instance = new Managers();
	}

    return m_instance;
}