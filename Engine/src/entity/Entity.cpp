#include "Entity.h"

Entity::Entity()
{
	vertices[0] = -0.5f;
	vertices[1] = -0.5f;
	vertices[2] = 0.0f;
	vertices[3] = 0.5f;
	vertices[4] = -0.5f;
	vertices[5] = 0.0f;
	vertices[6] = 0.5f;
	vertices[7] = 0.5f;
	vertices[8] = 0.0f;
	vertices[9] = -0.5f;
	vertices[10] = 0.5f;
	vertices[11] = 0.0f;


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
}

Entity::~Entity()
{

}

unsigned int Entity::GetVerticesSize()
{
	return sizeof(vertices);
}

float* Entity::GetVertices()
{
	return vertices;
}

unsigned int Entity::GetIndicesSize()
{
	return sizeof(indices);
}

unsigned int* Entity::GetIndices()
{
	return indices;
}

void Entity::Draw()
{

}
