#include "Entity.h"

glm::vec3 Entity::CalculateCenter()
{
	float minX = verticesData[0], maxX = verticesData[0];
	float minY = verticesData[1], maxY = verticesData[1];

	for (int i = 0; i < verticesData.size(); i += 9)
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
	translation = glm::vec3(1.0f);
	rotation = glm::mat4(1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);
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
	return translation;
}

glm::vec3 Entity::GetRotation()
{
	return glm::vec3(rotation[0][0], rotation[1][1], rotation[2][2]);
}

glm::vec3 Entity::GetScale()
{
	return scale;
}

void Entity::SetPosition(float x, float y, float z)
{
	translation = glm::vec3(x, y, z);

	UpdateTRS();
}

void Entity::SetRotation(float x, float y, float z)
{
	rotation = glm::mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	glm::vec3 center = CalculateCenter();

	rotation = glm::translate(rotation, center);
	rotation = glm::rotate(rotation, glm::radians(x), glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, glm::radians(y), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(z), glm::vec3(0, 0, 1));
	rotation = glm::translate(rotation, -center);

	UpdateTRS();
}

void Entity::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);

	UpdateTRS();
}

void Entity::UpdateTRS()
{
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 rotationMatrix = rotation;
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	trs = translateMatrix * rotationMatrix * scaleMatrix;
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
	return translation.x;
}

float Entity::GetY()
{
	return translation.y;
}

float Entity::GetZ()
{
	return translation.z;
}

void Entity::Draw()
{

}
