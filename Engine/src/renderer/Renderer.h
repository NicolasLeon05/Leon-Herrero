#pragma once
#include "GL/glew.h"
#include "../window/Window.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <vector>

using namespace std;

class Entity2D;

class Shape;
class Sprite;

class Renderer
{
public:
	static vector<Entity2D*> entities;
	static glm::mat4 mvp;
	Renderer();
	~Renderer();
	
	static void MakeContextCurrent(Window window);
	static void Clear();
	static void SwapBuffers(Window window);
	static void SetMVP(Window window);
	static bool IsInEntities(Entity2D* entity);
	static void InitShapeBuffers(Shape& shape);
	static void InitSpriteBuffers(Sprite& sprite);
	static void PollEvents();
	static void Draw(Shape* shape, GLsizei count);
	static void Draw(Sprite* sprite, GLsizei count);
};