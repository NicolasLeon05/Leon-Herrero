#pragma once

class BaseGame
{
protected:
	virtual void InitGame() = 0;
	virtual void Update() = 0;
	virtual void DeInitGame() = 0;
};