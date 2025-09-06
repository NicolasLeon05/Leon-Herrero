#pragma once

#include "../renderer/Renderer.h"

class Entity
{
private:
	float vertices[12];
	unsigned int indices[6];
	float color[4];

public:
	Entity();
	~Entity();

	unsigned int GetVerticesSize();
	float* GetVertices();

	unsigned int GetIndicesSize();
	unsigned int* GetIndices();

	 virtual void Draw() = 0;
};