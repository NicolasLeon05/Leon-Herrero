#include "Window.h"

Window::Window()
{
	glfwWindow = nullptr;
	width = 640;
	height = 480;
	title = "Hello World";
}

Window::Window(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;
	this->title = title;
}

Window::~Window()
{

}

void Window::CreateWindow()
{
	glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!glfwWindow)
	{
		glfwTerminate();
		exit(-1);
	}
}

GLFWwindow* Window::GetGlfwWindow()
{
	return glfwWindow;
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(glfwWindow);
}
