#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "BaseGame.h"
#include "window/Window.h"

class Game : public BaseGame
{
public:
	void InitGame() override;
	void Update() override;
	void DeInitGame() override;
};

Shape square = Shape();

Shape triangle1 = Shape();
Shape triangle2 = Shape();

static const float screenWidth = 720.0f;
static const float screenHeight = 480.0f;

float width = 100.0f;
float height = 100.0f;

float triangleRotation = 0.1;

float elapsedTime = 0.0f;
float elapsedTimeMax = 10.0f;
float elapsedTimeMin = 0.0f;

bool elapsedTimeReachedMax;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{
	Vertex v1 = Vertex(0.0f, screenHeight, 0.1f);
	square.CreateSquare(v1, width, height, Color::BLUE);

	Vertex v2 = Vertex(screenWidth / 2 - 300.0f, screenHeight / 2 - 100, 0.1, Color::RED);
	Vertex v3 = Vertex(screenWidth / 2 - 250, screenHeight / 2 - 50, 0.1, Color::RED);
	Vertex v4 = Vertex(screenWidth / 2 - 200, screenHeight / 2 - 100, 0.1, Color::RED);
	triangle1.CreateTriangle(v2, v3, v4);

	Vertex v5 = Vertex(screenWidth / 2 - 300.0f, screenHeight / 2 - 65, 0.1, Color::RED);
	Vertex v6 = Vertex(screenWidth / 2 - 250, screenHeight / 2 - 130, 0.1, Color::RED);
	Vertex v7 = Vertex(screenWidth / 2 - 200, screenHeight / 2 - 65, 0.1, Color::RED);
	triangle2.CreateTriangle(v5, v6, v7);
}

void Game::Update()
{
	float translateInX = 1.0f;
	float translateInY = 1.0f;

	square.Rotate(0.0f, 0.0f, 1.0f);
	square.Translate(translateInX, 0.0f, 0.0f);

	if (elapsedTimeReachedMax)
	{
		triangle1.Rotate(0.0f, 0.0f, triangleRotation - elapsedTime);
		triangle2.Rotate(0.0f, 0.0f, -triangleRotation + elapsedTime);
		elapsedTime -= 1;
	}

	else if (!elapsedTimeReachedMax)
	{
		triangle1.Rotate(0.0f, 0.0f, triangleRotation - elapsedTime);
		triangle2.Rotate(0.0f, 0.0f, -triangleRotation + elapsedTime);
		elapsedTime += 1;
	}

	if (elapsedTime >= elapsedTimeMax)
	{
		elapsedTimeReachedMax = true;
	}
	if (elapsedTime <= elapsedTimeMin)
	{
		elapsedTimeReachedMax = false;
	}

	square.Draw();
	triangle1.Draw();
	triangle2.Draw();
}

void Game::DeInitGame()
{

}
