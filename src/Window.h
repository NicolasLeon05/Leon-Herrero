#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	GLFWwindow* glfwWindow;
	int width;
	int height;
	const char* title;

public:
	Window();
	Window(int width, int height, const char* title);
	~Window();

	void CreateWindow();
	GLFWwindow* GetGlfwWindow();
	int GetWidth();
	int GetHeight();

	bool ShouldClose();
};