#pragma once
// hacerlo único pude ser un singleton
#include "GL/glew.h"
#include "../window/Window.h"

class Entity2D;

class Renderer
{
public:
	Renderer();
	~Renderer();
	
	static void MakeContextCurrent(Window window);
	static void Clear();
	static void SwapBuffers(Window window);
	static void DrawEntity(Entity2D& entity);
	static void PollEvents();
	static void DrawArrays(GLenum primitive, GLint first, GLsizei count);
};