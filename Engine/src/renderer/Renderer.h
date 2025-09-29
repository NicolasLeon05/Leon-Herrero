#pragma once
// hacerlo único pude ser un singleton
#include "GL/glew.h"
#include "../window/Window.h"

#include "glm.hpp"

#include <vector>

using namespace std;

class Entity2D;

class Renderer
{
public:
	static vector<Entity2D*> shapes;
	Renderer();
	~Renderer();
	
	static void MakeContextCurrent(Window window);
	static void Clear();
	static void SwapBuffers(Window window);
	static bool IsInShapes(Entity2D* entity);
	static void InitShapeBuffers(Entity2D& entity);
	static void PollEvents();
	static void Draw(Entity2D* entity, GLsizei count);
};