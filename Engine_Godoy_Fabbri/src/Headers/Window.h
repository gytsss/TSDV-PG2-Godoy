#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>

namespace ToToEng
{
	class Window
	{
	private:
		static Window* instance;
		int width;
		int height;
		const char* title;
		GLFWwindow* window;

	public:
		Window();
		Window(int width, int height, const char* title);
		~Window();

		static Window* getInstance();
		
		GLFWwindow* getWindow();
		bool shouldClose();

		int getWidth();
		int getHeight();
	};
}