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

static const float screenWidth = 720.0f;
static const float screenHeight = 640.0f;

float sWidth = 100;
float sHeight = 100;
float sX = 0;
float sY = screenHeight - sHeight;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{

	//square.SetTexture("texture.jpg", 301, 167);
	//square.CreateSquare(v7, sWidth, sHeight, Color::WHITE);

	squareAnim.SetTexture("pokemon.png", 256, 256);
	squareAnim.GetAnimation()->AddFrames(0, 128, 64, 64, 256, 256, 1, 4);
	glm::vec3 position = { 100.0f, 100.0f, 0.0f };
	squareAnim.CreateSquare(position, 200.0f, 200.0f);

}

void Game::Update()
{
	float posChangeX = 0.0f;
	float posChangeY = 0.0f;
	//triangle1.SetRotatation(0.0f, 0.0f, rotation);

	//Multiplicar pos change por deltatime
	if (Input::IsKeyDown(Key::A))
	{
		posChangeX = -1;
	}

	if (Input::IsKeyDown(Key::D))
		posChangeX = 1;

	if (Input::IsKeyDown(Key::W))
		posChangeY = 1;

	if (Input::IsKeyDown(Key::S))
		posChangeY = -1;

	squareAnim.GetAnimation()->Update();

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
