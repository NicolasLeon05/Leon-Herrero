#pragma once

#include "../EngineAPI.h"

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
	float s;
	float t;
	Color color;

	void AssignColor();
public:
	ENGINE_API Vertex(float x, float y, float z);
	ENGINE_API Vertex(float x, float y, float z, Color color);
	ENGINE_API Vertex(float x, float y, float z, Color color, float alpha);
	ENGINE_API ~Vertex();

	ENGINE_API float GetPosX();
	ENGINE_API float GetPosY();
	ENGINE_API float GetPosZ();
	ENGINE_API float GetR();
	ENGINE_API float GetG();
	ENGINE_API float GetB();
	ENGINE_API float GetA();
	float GetS();
	float GetT();
	ENGINE_API Color GetColor();

	ENGINE_API void SetPosX(float x);
	ENGINE_API void SetPosY(float y);
	ENGINE_API void SetPosZ(float z);


	ENGINE_API void SetColor(Color color);
	ENGINE_API void SetColor(Color color, float alpha);
};