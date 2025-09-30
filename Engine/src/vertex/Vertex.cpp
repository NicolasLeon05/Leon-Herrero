#include "Vertex.h"

void Vertex::AssignColor()
{
	switch (color)
	{
	case Color::WHITE:
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		break;
	case Color::RED:
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
		break;
	case Color::GREEN:
		r = 0.0f;
		g = 1.0f;
		b = 0.0f;
		break;
	case Color::BLUE:
		r = 0.0f;
		g = 0.0f;
		b = 1.0f;
		break;
	case Color::BLACK:
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		break;
	case Color::ORANGE:
		r = 1.0f;
		g = 0.6f;
		b = 0.0f;
		break;
	}
}

Vertex::Vertex(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	color = Color::WHITE;
	a = 1.0f;
	AssignColor();
}

Vertex::Vertex(float x, float y, float z, Color color)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->color = color;
	a = 1.0f;
	AssignColor();
}

Vertex::Vertex(float x, float y, float z, Color color, float alpha)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->color = color;
	a = alpha;

	AssignColor();
}

Vertex::~Vertex()
{

}

float Vertex::GetPosX()
{
	return x;
}

void Vertex::SetPosX(float x)
{
	this->x = x;
}

float Vertex::GetPosY()
{
	return y;
}

void Vertex::SetPosY(float y)
{
	this->y = y;
}

float Vertex::GetPosZ()
{
	return z;
}

void Vertex::SetPosZ(float z)
{
	this->z = z;
}

float Vertex::GetR()
{
	return r;
}

float Vertex::GetG()
{
	return g;
}

float Vertex::GetB()
{
	return b;
}

float Vertex::GetA()
{
	return a;
}

Color Vertex::GetColor()
{
	return color;
}

void Vertex::SetColor(Color color)
{
	this->color = color;

	AssignColor();
}

void Vertex::SetColor(Color color, float alpha)
{
	this->color = color;
	a = alpha;

	AssignColor();
}
