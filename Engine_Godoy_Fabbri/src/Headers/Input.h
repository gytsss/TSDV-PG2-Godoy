#pragma once

#include <list>

#include "Window.h"
#include "Exports.h"

namespace ToToEng
{
	class TOTO_API Input
	{
	private:
		static Input* instance;
		GLFWwindow* window;
		
		explicit Input();

	public:
		enum KeyCode
		{
			a = GLFW_KEY_A,
			b = GLFW_KEY_B,
			c = GLFW_KEY_C,
			d = GLFW_KEY_D,
			e = GLFW_KEY_E,
			f = GLFW_KEY_F,
			g = GLFW_KEY_G,
			h = GLFW_KEY_H,
			i = GLFW_KEY_I,
			j = GLFW_KEY_J,
			k = GLFW_KEY_K,
			l = GLFW_KEY_L,
			m = GLFW_KEY_M,
			n = GLFW_KEY_N,
			o = GLFW_KEY_O,
			p = GLFW_KEY_P,
			q = GLFW_KEY_Q,
			r = GLFW_KEY_R,
			s = GLFW_KEY_S,
			t = GLFW_KEY_T,
			u = GLFW_KEY_U,
			v = GLFW_KEY_V,
			w = GLFW_KEY_W,
			x = GLFW_KEY_X,
			y = GLFW_KEY_Y,
			z = GLFW_KEY_Z,
			
		};

		enum Action
		{
			Pressed = GLFW_PRESS,
			Repeated = GLFW_REPEAT,
			Released = GLFW_RELEASE,
		};

		struct KeyState
		{
			KeyCode key;
			Action state;
		};

		static std::list<KeyCode> keysPressed;
		
		static Input* getInstance();

		static bool getKey(KeyCode keyCode, Action action);
	};

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}