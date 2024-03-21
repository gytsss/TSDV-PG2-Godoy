#include "Input.h"

namespace ToToEng
{
	std::list<Input::KeyCode> Input::keysPressed;

	Input* Input::instance = nullptr;
	
	Input::Input()
	{
		if (instance != nullptr && this != instance)
		{
			delete this;
			return;
		}
		
		instance = this;

		window = Window::getInstance()->getWindow();
		
		glfwSetKeyCallback(window, keyCallback);
	}

	Input* Input::getInstance()
	{
		if (!instance)
			instance = new Input();

		return instance;
	}

	bool Input::getKey(const KeyCode keyCode, const Action action)
	{
		switch (action)
		{
			case Pressed:
			{
				const bool pressed = std::find(keysPressed.begin(), keysPressed.end(), keyCode) != keysPressed.end();
				keysPressed.remove(keyCode);
				return pressed;
			}

			case Repeated:
			{
				return glfwGetKey(getInstance()->window, keyCode) == Pressed;
			}

			case Released:
			{
				return glfwGetKey(getInstance()->window, keyCode) == Released;
			}
		}

		return false;
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, const int action, int mods)
	{
		switch (action)
		{
		case GLFW_RELEASE:
			Input::keysPressed.remove(static_cast<Input::KeyCode>(key));
			break;

		case GLFW_PRESS:
			Input::keysPressed.push_back(static_cast<Input::KeyCode>(key));
			break;

		default:;
		}
	}
}