#pragma once
#include "GL/glew.h"
#include "../window/Window.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <vector>

using namespace std;

class Entity2D;

class Renderer
{
public:
	static vector<Entity2D*> shapes;
	static glm::mat4 mvp;
	Renderer();
	~Renderer();
	
	static void MakeContextCurrent(Window window);
	static void Clear();
	static void SwapBuffers(Window window);
	static void SetMvp(Window window);
	static bool IsInShapes(Entity2D* entity);
	static void InitShapeBuffers(Entity2D& entity);
	static void PollEvents();
	static void Draw(Entity2D* entity, GLsizei count);
};