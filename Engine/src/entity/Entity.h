#pragma once

#include <vector>

class Entity
{
protected:
	std::vector<float> verticesData;
	std::vector <unsigned int> indices;
	float color[4];
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;

public:
	Entity();
	~Entity();

	unsigned int* GetVBO();
	unsigned int* GetEBO();
	unsigned int* GetVAO();

	unsigned int GetVerticesSize();
	float* GetVertices();

	unsigned int GetIndicesSize();
	unsigned int* GetIndices();

	virtual void Draw() = 0;
	virtual void SetVertices(float posX, float posY, float posZ) = 0;
};