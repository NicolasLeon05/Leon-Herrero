#include "Entity.h"

glm::vec3 Entity::CalculateCenter()
{
	float minX = verticesData[0], maxX = verticesData[0];
	float minY = verticesData[1], maxY = verticesData[1];

	for (int i = 0; i < verticesData.size(); i += 7)
	{
		float x = verticesData[i];
		float y = verticesData[i + 1];

		if (x < minX) minX = x;
		if (x > maxX) maxX = x;
		if (y < minY) minY = y;
		if (y > maxY) maxY = y;
	}

	float centerX = (minX + maxX) / 2.0f;
	float centerY = (minY + maxY) / 2.0f;

	return glm::vec3(centerX, centerY, 0.0f);
}

Entity::Entity()
{
	trs = glm::mat4(1.0f);
	position = glm::vec3(1.0f);
	rotation = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Entity::~Entity()
{

}

unsigned int* Entity::GetVBO()
{
	return &VBO;
}

unsigned int* Entity::GetEBO()
{
	return &EBO;
}

unsigned int* Entity::GetVAO()
{
	return &VAO;
}

glm::mat4 Entity::GetTRS()
{
	return trs;
}

glm::vec3 Entity::GetPosition()
{
	return position;
}

glm::vec4 Entity::GetRotation()
{
	return rotation;
}

glm::vec3 Entity::GetScale()
{
	return scale;
}

void Entity::Translate(float x, float y, float z)
{
	position += glm::vec3(x, y, z);

	trs = glm::translate(trs, glm::vec3(x, y, z));
}

void Entity::Rotate(float x, float y, float z)
{
	glm::vec3 center = CalculateCenter();

	trs = glm::translate(trs, center);
	trs = glm::rotate(trs, glm::radians(x), glm::vec3(1, 0, 0));
	trs = glm::rotate(trs, glm::radians(y), glm::vec3(0, 1, 0));
	trs = glm::rotate(trs, glm::radians(z), glm::vec3(0, 0, 1));
	trs = glm::translate(trs, -center);
}

void Entity::Scale(float x, float y, float z)
{
	glm::vec3 center = CalculateCenter();

	trs = glm::translate(trs, center);
	scale = glm::vec3(x, y, z);
	trs = glm::scale(trs, scale);
	trs = glm::translate(trs, -center);
}

unsigned int Entity::GetVerticesSize()
{
	return static_cast<unsigned int> (verticesData.size() * sizeof(float));
}

float* Entity::GetVertices()
{
	return &verticesData[0];
}

unsigned int Entity::GetIndicesSize()
{

	return static_cast<unsigned int> (indices.size() * sizeof(unsigned int));
}

int Entity::GetIndicesCount()
{
	return indices.size();
}

unsigned int* Entity::GetIndices()
{
	return &indices[0];
}

float Entity::GetX()
{
	return position.x;
}

float Entity::GetY()
{
	return position.y;
}

float Entity::GetZ()
{
	return position.z;
}

void Entity::Draw()
{

}
