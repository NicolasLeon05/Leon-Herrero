#pragma once

#include "EngineAPI.h"

class BaseGame
{
protected:
	virtual void InitGame() = 0;
	virtual void Update() = 0;
	virtual void DeInitGame() = 0;

public:
	ENGINE_API int RunEngine();
};