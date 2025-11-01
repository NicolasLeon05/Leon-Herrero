#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "sprite/Sprite.h"
#include "BaseGame.h"
#include "window/Window.h"
#include "input/Input.h"

class Game : public BaseGame
{
public:
	void InitGame() override;
	void Update() override;
	void DeInitGame() override;
};

Shape triangle1 = Shape();
Shape triangle2 = Shape();

Sprite square = Sprite();

static const float screenWidth = 720;
static const float screenHeight = 640.0f;

float sWidth = 400;
float sHeight = 400;
float sX = 100.0f;
float sY = screenHeight / 2 + 100;

float rotation = 0.0f;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{
	Vertex v1 = Vertex(600.0f, 250.0f, 0.0f, Color::BLUE);
	Vertex v2 = Vertex(650.0f, 400.0f, 0.0f, Color::GREEN);
	Vertex v3 = Vertex(700, 350.0f, 0.0f, Color::WHITE);
	triangle1.CreateTriangle(v1, v2, v3);

	Vertex v7 = Vertex(sX, sY, 0.0f);

	square.SetTexture("texture.jpg", 301, 167);
	square.CreateSquare(v7, sWidth, sHeight, Color::WHITE);
	triangle1.SetPosition(0.0f, 0.0f, 0.0f);
}

void Game::Update()
{
	//triangle1.SetRotatation(0.0f, 0.0f, rotation);


	if (Input::IsKeyDown(Key::A))
	{
		rotation += 0.1f;
		triangle1.SetPosition(-rotation, 0.0f, 0.0f);
	}

	triangle1.SetScale(1.0f, 1.0f, 1.0f);

	//float right = sX + sWidth + square.GetX();

	//if (right >= screenWidth)
	//{
	//	square.Translate(0.0f, 1.0f, 0.0f);
	//}
	//else
	//{
	//	square.Translate(1.0f, 0.0f, 0.0f);
	//}
	square.Draw();
	triangle1.Draw();
}

void Game::DeInitGame()
{

}
