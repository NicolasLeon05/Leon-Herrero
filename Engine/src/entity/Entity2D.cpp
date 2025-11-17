#include "Entity2D.h"

#include "../renderer/Renderer.h"

Entity2D::Entity2D()
{
	material = Material();
}

Entity2D::~Entity2D()
{

}

Material& Entity2D::GetMaterial()
{
	return material;
}

void Entity2D::SetMaterial()
{
	material = material.ParseShader();
}

float Entity2D::GetCollisionWidth()
{
	return scale.x;
}

float Entity2D::GetCollisionHeight()
{
	return scale.y;
}

void Entity2D::Draw()
{
	
}
