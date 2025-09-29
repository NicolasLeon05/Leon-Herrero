#pragma once

#include "GLFW/glfw3.h"
#include "../EngineAPI.h"
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
	ENGINE_API Window(int width, int height, const char* title);
	ENGINE_API ~Window();

	void CreateWindow();
	GLFWwindow* GetGlfwWindow();
	ENGINE_API int GetWidth();
	ENGINE_API int GetHeight();

	bool ShouldClose();
};