#pragma once

#include "../window/Window.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	
	void MakeContextCurrent(Window window);
	void Clear();
	void SwapBuffers(Window window);
};