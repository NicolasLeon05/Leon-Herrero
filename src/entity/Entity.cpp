#include "Entity.h"

Entity::Entity()
{
	vertices[0] = -0.5f;
	vertices[1] = -0.5f;
	vertices[2] = 0.0f;
	vertices[3] = 0.5f;
	vertices[4] = -0.5f;
	vertices[5] = 0.0f;
	vertices[6] = 0.0f;
	vertices[7] = 0.5f;
	vertices[8] = 0.0f;
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
