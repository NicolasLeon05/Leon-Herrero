#pragma once

#include <vector>

class Entity
{
protected:
	std::vector<float> vertices;
	std::vector <unsigned int> indices;
	float color[4];

public:
	Entity();
	~Entity();

	unsigned int GetVerticesSize();
	float* GetVertices();

	unsigned int GetIndicesSize();
	unsigned int* GetIndices();

	virtual void Draw() = 0;
	virtual void SetVertices(float posX, float posY, float posZ) = 0;
};