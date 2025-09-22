#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "BaseGame.h"

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

void main()
{
	Game game;

	Vertex v1 = Vertex(300.0f, 250.0f, 0.0f, Color::BLUE);
	Vertex v2 = Vertex(300.0f, 400.0f, 0.0f, Color::GREEN);
	Vertex v3 = Vertex(500, 350.0f, 0.0f, Color::WHITE);

	Shape triangle1 = Shape();
	triangle1.CreateTriangle(v1, v2, v3); //Color::WHITE);

	Vertex v4 = Vertex(400.0f, 200.0f, 0.0f, Color::BLUE, 0.5f);
	Vertex v5 = Vertex(450.0f, 400.0f, 0.0f, Color::BLUE, 0.5f);
	Vertex v6 = Vertex(300.0f, 200.0f, 0.0f, Color::BLUE, 0.5f);

	Shape triangle2 = Shape();
	triangle2.CreateTriangle(v4, v5, v6); //Color::WHITE);

	float x = 100.0f;
	float y = 150.0f;
	float sWidht = 200.0f;
	float sHeight = 200.0f;

	Vertex v7 = Vertex(x, y, 0.0f);

	Shape square = Shape();
	square.CreateSquare(v7, sWidht, sHeight, Color::GREEN, 1.0f);

	game.RunEngine();
}

void Game::InitGame()
{

}

void Game::Update()
{

}

void Game::DeInitGame()
{

}
