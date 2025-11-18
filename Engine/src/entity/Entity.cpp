#include "Entity.h"


Entity::Entity()
{
	translation = glm::vec3(1.0f);
	prevPosition  = glm::vec3(-1.0f);
	rotation = glm::mat4(1.0f);
	eulerRotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	UpdateTRS();
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

glm::vec3 Entity::GetPrevPosition()
{
	return prevPosition;
}

glm::vec3 Entity::GetRotation()
{
	return eulerRotation;
}

glm::vec3 Entity::GetScale()
{
	return scale;
}

void Entity::SetPosition(float x, float y, float z)
{
	prevPosition = translation;
	translation = glm::vec3(x, y, z);
	UpdateTRS();
}

void Entity::SetPosition(glm::vec3 position)
{
	prevPosition = translation;
	translation = position;
	UpdateTRS();
}

void Entity::SetRotation(float x, float y, float z)
{
	eulerRotation = glm::vec3(x, y, z);

	rotation = glm::mat4(1);
	rotation = glm::rotate(rotation, glm::radians(x), glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, glm::radians(y), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(z), glm::vec3(0, 0, 1));

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

void Entity::SetX(float x)
{
	translation.x = x;

	UpdateTRS();
}

void Entity::SetY(float y)
{
	translation.y = y;

	UpdateTRS();
}

void Entity::SetZ(float z)
{
	translation.z = z;

	UpdateTRS();
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

void Entity::Update()
{

}

void Entity::Draw()
{

}
