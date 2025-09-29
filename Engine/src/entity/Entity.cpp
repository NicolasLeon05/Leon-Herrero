#include "Entity.h"

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
	position = glm::vec3(x, y, z);

	trs = glm::translate(trs, position);
}

void Entity::Rotate(float x, float y, float z)
{
	trs = glm::rotate(trs, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	trs = glm::rotate(trs, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	trs = glm::rotate(trs, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::Scale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);

	trs = glm::scale(trs, scale);
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

void Entity::Draw()
{

}
