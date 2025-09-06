#include "Entity2D.h"

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

void Entity2D::Draw()
{
	Renderer::DrawEntity(*this);

	GetMaterial().SetFilepath("src/material/Basic.shader");
	SetMaterial();
	std::cout << "Vertex" << std::endl;
	std::cout << GetMaterial().GetVertexSource() << std::endl;
	std::cout << "Fragment" << std::endl;
	std::cout << GetMaterial().GetFragmentSource() << std::endl;
}

