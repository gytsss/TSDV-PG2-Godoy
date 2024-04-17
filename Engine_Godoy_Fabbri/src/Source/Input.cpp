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

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetCursorPosCallback(window, mouse_callback);
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

	glm::vec2 Input::getMouseDelta()
	{
		return getInstance()->mouseDelta;
	}

	void Input::resetMouseDelta()
	{
		getInstance()->mouseDelta = {0,0};
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

	void mouse_callback(GLFWwindow* window, double posX, double posY)
	{
		if (Input::getInstance()->firstMouse) // initially set to true
		{
			Input::getInstance()->lastX = posX;
			Input::getInstance()->lastY = posY;
			Input::getInstance()->firstMouse = false;
		}

		float offsetX = posX - Input::getInstance()->lastX;
		float offsetY = Input::getInstance()->lastY - posY;
		Input::getInstance()->lastX = posX;
		Input::getInstance()->lastY = posY;

		Input::getInstance()->mouseDelta.x = offsetX;
		Input::getInstance()->mouseDelta.y = offsetY;

	}
}
