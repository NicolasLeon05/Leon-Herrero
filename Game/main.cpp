#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "sprite/Sprite.h"
#include "BaseGame.h"
#include "window/Window.h"
#include "input/Input.h"
#include "glm.hpp"

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
Sprite squareAnim = Sprite();

static const float screenWidth = 720;
static const float screenHeight = 640.0f;

float sWidth = screenWidth / 4;
float sHeight = screenHeight / 4;
float sX = screenWidth / 2;
float sY = screenHeight / 2;



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


	squareAnim.SetTexture("pokemon.png", 1, 1);
	squareAnim.GetAnimation()->AddFrames(0, 128, 64, 64, 256, 256, 1, 4);
	squareAnim.CreateSquare(v7, sWidth, sHeight, Color::WHITE);

	//squareAnim.SetRotation(0.0f, 0.0f, 0.0f);

	triangle1.SetPosition(0.0f, 0.0f, 0.0f);
}

void Game::Update()
{
	float posChangeX = 0.0f;
	float posChangeY = 0.0f;
	//triangle1.SetRotatation(0.0f, 0.0f, rotation);


	if (Input::IsKeyDown(Key::A))
	{
		posChangeX = -2;
		squareAnim.GetAnimation()->Update();
	}

	if (Input::IsKeyDown(Key::D))
	{
		posChangeX = 2;
	}

	if (Input::IsKeyDown(Key::W))
	{
		posChangeY = -2;
	}

	if (Input::IsKeyDown(Key::S))
	{
		posChangeY = 2;
	}


	squareAnim.SetPosition(squareAnim.GetPosition().x + posChangeX, squareAnim.GetPosition().y + posChangeY, 0);
	//glm::vec3 asd = squareAnim.GetPosition().x;

	cout << "Position: " << squareAnim.GetPosition().x << ", " << squareAnim.GetPosition().y << ", " << squareAnim.GetPosition().z << endl;


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
	//square.Draw();
	//triangle1.Draw();

	squareAnim.Draw();
}

void Game::DeInitGame()
{

}
