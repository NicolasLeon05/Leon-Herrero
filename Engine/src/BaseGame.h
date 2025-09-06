#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

class BaseGame
{
protected:
	virtual void InitGame() = 0;
	virtual void Update() = 0;
	virtual void DeInitGame() = 0;

public:
	ENGINE_API int RunEngine();
};