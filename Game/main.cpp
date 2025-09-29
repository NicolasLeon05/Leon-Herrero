#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "BaseGame.h"
#include "window/Window.h"

// preguntar a stef como hacer para que los includes no necesiten de incluir
// los .h de las librerias y si pueden estar aparte

/*
preguntar como funciona bien esto
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
*/

class Game : public BaseGame
{
public:
	void InitGame() override;
	void Update() override;
	void DeInitGame() override;
};

Shape triangle1 = Shape();
Shape triangle2 = Shape();
Shape square = Shape();

static const float screenWidth = 1920.0f;
static const float screenHeight = 1080.0f;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{
	Vertex v1 = Vertex(screenWidth / 2 - 100.0f, screenHeight / 2 - 50, 0.0f, Color::BLUE);
	Vertex v2 = Vertex(screenWidth / 2 + 100.0f, screenHeight / 2 - 50, 0.0f, Color::GREEN);
	Vertex v3 = Vertex(screenWidth / 2, screenHeight / 2 + 50, 0.0f, Color::WHITE);

	triangle1.CreateTriangle(v1, v2, v3); //Color::WHITE);

	Vertex v4 = Vertex(400.0f, 200.0f, 0.0f, Color::BLUE, 0.5f);
	Vertex v5 = Vertex(450.0f, 400.0f, 0.0f, Color::BLUE, 0.5f);
	Vertex v6 = Vertex(300.0f, 200.0f, 0.0f, Color::BLUE, 0.5f);
	
	triangle2.CreateTriangle(v4, v5, v6); //Color::WHITE);
	
	float x = 100.0f;
	float y = 150.0f;
	float sWidht = 200.0f;
	float sHeight = 200.0f;
	
	Vertex v7 = Vertex(x, y, 0.0f);
	
	square.CreateSquare(v7, sWidht, sHeight, Color::GREEN, 1.0f);
}

void Game::Update()
{
	//triangle1.Rotate(0.0f, 0.0f, 0.01f);
	//triangle1.Scale(1.0f, 1.0f, 1.0f);
	//triangle1.Translate(0.0f, 0.1f, 0.0f);
	triangle1.Draw();
	triangle2.Draw();
	square.Draw();
}

void Game::DeInitGame()
{

}
