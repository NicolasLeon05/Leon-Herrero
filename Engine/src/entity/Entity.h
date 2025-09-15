#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <vector>

class Entity
{
protected:
	std::vector<float> verticesData;
	std::vector <unsigned int> indices;

	glm::mat4 trs;
	glm::vec3 position;
	glm::vec4 rotation;
	glm::vec3 scale;

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

	glm::mat4 GetTRS();
	glm::vec3 GetPosition();
	glm::vec4 GetRotation();
	glm::vec3 GetScale();

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);

	unsigned int GetVerticesSize();
	float* GetVertices();

	unsigned int GetIndicesSize();
	unsigned int* GetIndices();

	virtual void Draw() = 0;
	virtual void SetVertices(float posX, float posY, float posZ) = 0;
};