#pragma once

#include "window/Window.h"
#include "CollisionManager/CollisionManager.h"

ENGINE_API class BaseGame
{
protected:
	virtual void InitGame() = 0;
	virtual void Update() = 0;
	virtual void DeInitGame() = 0;

	CollisionManager collisionManager;

public:
	ENGINE_API int RunEngine(Window window);
};