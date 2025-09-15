#pragma once

#include "Color.h"

class Vertex
{
private:
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
	Color color;

	void AssignColor();
public:
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, Color color);
	Vertex(float x, float y, float z, Color color, float alpha);
	~Vertex();

	float GetPosX();
	float GetPosY();
	float GetPosZ();
	float GetR();
	float GetG();
	float GetB();
	float GetA();
	Color GetColor();

	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);


	void SetColor(Color color);
	void SetColor(Color color, float alpha);
};