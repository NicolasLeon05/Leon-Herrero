#include "Entity.h"


Entity::Entity()
{

}

Entity::~Entity()
{

}

unsigned int Entity::GetVerticesSize()
{
	return static_cast<unsigned int> (vertices.size() * sizeof(float));
}

float* Entity::GetVertices()
{
	return &vertices[0];
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
