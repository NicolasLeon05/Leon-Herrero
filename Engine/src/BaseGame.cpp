#include "shape/Shape.h"
#include "renderer/Renderer.h"
#include "clock/Clock.h"
#include "window/Window.h"
#include "input/Input.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "BaseGame.h"

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int BaseGame::RunEngine(Window window)
{
	if (!glfwInit())
		return -1;

	window.CreateWindow();

	Renderer::MakeContextCurrent(window);
	Input::Init(window.GetGlfwWindow());

	glewInit();
	InitGame();
	Renderer::SetMVP(window);

	MyClock::InitClock();

	while (!window.ShouldClose())
	{
		Input::Update();
		Renderer::PollEvents();

		Renderer::Clear();
		Update();

		MyClock::UpdateDeltaTime();
		Renderer::SwapBuffers(window);
	}

	DeInitGame();

	for (int i = 0; i < Renderer::entities.size(); i++)
	{
		Renderer::entities[i]->GetMaterial().DeinitShader();
	}

	glfwTerminate();
	return 0;
}