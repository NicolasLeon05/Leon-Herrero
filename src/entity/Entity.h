#pragma once

#include "../renderer/Renderer.h"

class Entity
{
private:
	float vertices[9];
	float color[4];

public:
	Entity();
	~Entity();

	unsigned int GetVerticesSize();
	float* GetVertices();

	 virtual void Draw() = 0;
};