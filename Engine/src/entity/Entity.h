#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../EngineAPI.h"
#include <vector>

class Entity
{
protected:
	std::vector<float> verticesData;
	std::vector <unsigned int> indices;

	glm::mat4 trs;
	glm::vec3 translation;
	glm::mat4 rotation;
	glm::vec3 scale;

	float color[4];

	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;

	glm::vec3 CalculateCenter();

public:
	Entity();
	~Entity();

	unsigned int* GetVBO();
	unsigned int* GetEBO();
	unsigned int* GetVAO();

	glm::mat4 GetTRS();
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	void UpdateTRS();

	ENGINE_API void SetPosition(float x, float y, float z);
	ENGINE_API void SetRotatation(float x, float y, float z);
	ENGINE_API void SetScale(float x, float y, float z);

	unsigned int GetVerticesSize();
	float* GetVertices();

	unsigned int GetIndicesSize();
	int GetIndicesCount();
	unsigned int* GetIndices();

	ENGINE_API float GetX();
	ENGINE_API float GetY();
	ENGINE_API float GetZ();

	virtual void Draw() = 0;
};