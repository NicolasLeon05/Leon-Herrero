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

void Entity2D::Draw()
{
	Renderer::DrawShape(*this);

	GetMaterial().SetFilepath("Basic.shader");
	SetMaterial();
	std::cout << "Vertex" << std::endl;
	std::cout << GetMaterial().GetVertexSource() << std::endl;
	std::cout << "Fragment" << std::endl;
	std::cout << GetMaterial().GetFragmentSource() << std::endl;
}

void Entity2D::SetVertices(float posX, float posY, float posZ)
{
}

