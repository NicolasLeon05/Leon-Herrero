#include "Entity2D.h"

Entity2D::Entity2D()
{
	material = Material();
}

Entity2D::~Entity2D()
{

}

Material Entity2D::GetMaterial()
{
	return material;
}

void Entity2D::SetMaterial(std::string filepath)
{
	material.ParseShader(filepath);
}

