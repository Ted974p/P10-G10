#pragma once

#pragma region External Dependencies

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#pragma endregion

enum State {
	None,
	Pressed,
	Hold,
	Released
};

class Axis {
public:
	std::string name;

	sf::Keyboard::Key negative;
	sf::Keyboard::Key positive;

	sf::Joystick::Axis joystick;

	float value = 0;

	Axis(std::string name, sf::Keyboard::Key negative, sf::Keyboard::Key positive, sf::Joystick::Axis joystick);
};

class Key {
public:
	std::string name;

	sf::Keyboard::Key key;
	unsigned int button;

	bool hold;
	State current;

	Key(std::string name, sf::Keyboard::Key key, unsigned int button);
};

class InputManager {
private:

	static InputManager* m_instance;

	std::vector<Axis> axes {
		Axis("Horizontal", sf::Keyboard::Q, sf::Keyboard::D, sf::Joystick::X),
		Axis("Vertical", sf::Keyboard::Z, sf::Keyboard::S, sf::Joystick::Y),
		Axis("HorizontalArrows", sf::Keyboard::Left, sf::Keyboard::Right, sf::Joystick::X),
		Axis("VerticalArrows", sf::Keyboard::Up, sf::Keyboard::Down, sf::Joystick::Y)
	};
	
	std::vector<Key> keys{
		Key("quit", sf::Keyboard::Escape, 8),
		Key("Confirm", sf::Keyboard::K, 0),
		Key("Cancel", sf::Keyboard::K, 1),

		Key("Up", sf::Keyboard::Z, 2),
		Key("Left", sf::Keyboard::Q, 2),
		Key("Down", sf::Keyboard::S, 5),
		Key("Right", sf::Keyboard::D, 5),

		Key("UpArrow", sf::Keyboard::Up, 2),
		Key("LeftArrow", sf::Keyboard::Left, 2),
		Key("DownArrow", sf::Keyboard::Down, 5),
		Key("RightArrow", sf::Keyboard::Right, 5)
	};

	bool joystickConnected = false;

	float GetRawAxis(std::string name);
	State GetRawKey(std::string name);

	float GetJoystickValue(sf::Joystick::Axis axis);
	bool GetKeyValue(sf::Keyboard::Key key);
public:

	static InputManager* GetInstance();
	~InputManager();

	bool isJoystickConnected();

	void UpdateInputs();
	void UpdateEvents(sf::Event* event);

	float GetAxis(std::string name);
	
	bool GetKeyDown(std::string name);
	bool GetKey(std::string name);
	bool GetKeyUp(std::string name);
};

#define inputManager InputManager::GetInstance()