#include "Window.h"

namespace ToToEng
{
	Window* Window::instance = nullptr;
	
	Window::Window()
	{
		if (instance != nullptr && this != instance)
		{
			delete this;
			return;
		}

		instance = this;
		
		width = 854;
		height = 480;
		title = "Example game";

		window = NULL;

		if (!glfwInit())
			return;

		window = glfwCreateWindow(width, height, "Example game", NULL, NULL);

		if (!window)
		{
			delete this;
			return;
		}
		
		glfwMakeContextCurrent(window);
	}

	Window::Window(const int width, const int height, const char* title)
	{
		if (instance != nullptr && this != instance)
		{
			delete this;
			return;
		}
		
		instance = this;

		this->width = width;
		this->height = height;
		this->title = title;

		window = NULL;

		if (!glfwInit())
			return;

		window = glfwCreateWindow(width, height, title, NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK)
			std::cout << "An error has occurred while starting glew.";
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	Window* Window::getInstance()
	{
		if (!instance)
			instance = new Window();
		
		return instance;
	}

	GLFWwindow* Window::getWindow()
	{
		return window;
	}

	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	int Window::getWidth()
	{
		return width;
	}

	int Window::getHeight()
	{
		return height;
	}
}
