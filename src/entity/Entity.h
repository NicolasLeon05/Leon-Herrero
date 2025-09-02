#pragma once

#include "GL/glew.h"
#include "../renderer/Renderer.h"

class Entity
{
private:
	Renderer renderer;

	float vertices[9];
	float color[4];

public:
	Entity();
	~Entity();

	unsigned int GetVerticesSize();
	float* GetVertices();
};