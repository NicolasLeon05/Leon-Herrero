#include "Entity.h"

Entity::Entity()
{

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

unsigned int* Entity::GetIndices()
{
	return &indices[0];
}

void Entity::Draw()
{

}
