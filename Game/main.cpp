#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "sprite/Sprite.h"
#include "BaseGame.h"
#include "window/Window.h"

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
float sY = screenHeight/2 + 100;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{
	Vertex v7 = Vertex(sX, sY, 0.0f);

	square.SetTexturePath("texture.jpg");
	square.CreateSquare(v7, sWidth, sHeight, Color::WHITE);
}

void Game::Update()
{
	//triangle2.Rotate(0.0f, 0.0f, 0.01f);
	//square.Rotate(0.0f, 0.01f, -0.01f);
	//triangle1.Scale(1.0f, 1.0f, 1.0f);
	//triangle1.Translate(0.0f, 0.1f, 0.0f);

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
}

void Game::DeInitGame()
{

}
