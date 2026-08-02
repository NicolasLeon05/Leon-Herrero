#include "Game.h"
#include "window/Window.h"

static const float screenWidth = 320.0f * 2.5f;
static const float screenHeight = 320.0f * 2.5f;

void main()
{
	Window window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}