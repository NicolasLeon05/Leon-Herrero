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

static const float screenWidth = 1024.0f;
static const float screenHeight = 720.0f;
float triangleHeight = 100.0f;
float triangleWidth = 100.0f;

Vertex v1 = Vertex(screenWidth / 2 + 200.0f, screenHeight / 2 - triangleHeight / 2, 0.0f, Color::ORANGE);
Vertex v2 = Vertex(v1.GetPosX() + triangleWidth, v1.GetPosY(), 0.0f, Color::ORANGE);
Vertex v3 = Vertex(v1.GetPosX() + triangleWidth / 2, v1.GetPosY() + triangleHeight, 0.0f, Color::ORANGE);
Shape triangle1 = Shape();

Shape triangle2 = Shape();

Shape triangle3 = Shape();

float movement;
float initialRotationSpeed;
float currentRotationSpeed;
float rotationSpeedChange;
float maxRotationSpeed;
bool increasingSpeed;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{
	triangle1.CreateTriangle(v1, v2, v3);

	Vertex v4 = Vertex(screenWidth / 2 - 300, screenHeight / 2 - triangleHeight / 2, 0.0f, Color::RED);
	Vertex v5 = Vertex(v4.GetPosX() + triangleWidth, v4.GetPosY(), 0.0f, Color::RED);
	Vertex v6 = Vertex(v4.GetPosX() + triangleWidth / 2, v4.GetPosY() + triangleHeight, 0.0f, Color::RED);
	triangle2.CreateTriangle(v4, v5, v6);


	float heightOffset = 30;
	Vertex v7 = Vertex(screenWidth / 2 - 300, screenHeight / 2 + triangleHeight / 2 - heightOffset, 0.0f, Color::RED);
	Vertex v8 = Vertex(v7.GetPosX() + triangleWidth, v7.GetPosY(), 0.0f, Color::RED);
	Vertex v9 = Vertex(v7.GetPosX() + triangleWidth / 2, v7.GetPosY() - triangleHeight, 0.0f, Color::RED);
	triangle3.CreateTriangle(v7, v8, v9);


	movement = 1.0f;
	initialRotationSpeed = 1.0f;
	currentRotationSpeed = initialRotationSpeed;
	rotationSpeedChange = 0.01f;
	maxRotationSpeed = 7.0f;
	increasingSpeed = true;
}

void Game::Update()
{
	triangle1.Translate(0.0f, movement, 0.0f);

	if (v3.GetPosY() >= screenHeight || v3.GetPosY() <= 0)
	{
		triangle1.Rotate(90.0f, 0.0f, 0.0f);
		movement *= -1;
	}

	currentRotationSpeed += rotationSpeedChange;
	if (currentRotationSpeed >= maxRotationSpeed || currentRotationSpeed <= initialRotationSpeed)
		rotationSpeedChange *= -1;

	std::cout << "Current rotation speed: " << currentRotationSpeed << std::endl;
	triangle2.Rotate(0.0f, 0.0f, currentRotationSpeed);
	triangle3.Rotate(0.0f, 0.0f, -currentRotationSpeed);

	triangle1.Draw();
	triangle2.Draw();
	triangle3.Draw();
}

void Game::DeInitGame()
{

}
