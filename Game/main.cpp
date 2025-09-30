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


Shape triangle1 = Shape();
float movementSpeed;
float maxMovement;
float minMovement;
float triangle1Position;


Shape triangle2 = Shape();
Shape triangle3 = Shape();
float initialRotationSpeed;
float currentRotationSpeed;
float rotationSpeedChange;
float maxRotationSpeed;

Shape square = Shape();
float squareWidth;
float squareHight;
float maxScale;
float minScale;
float currentScale;
float scaleChangeSpeed;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{
	Vertex v1 = Vertex(screenWidth / 2 + 200.0f, screenHeight / 2 - triangleHeight / 2, 0.0f, Color::ORANGE);
	Vertex v2 = Vertex(v1.GetPosX() + triangleWidth, v1.GetPosY(), 0.0f, Color::ORANGE);
	Vertex v3 = Vertex(v1.GetPosX() + triangleWidth / 2, v1.GetPosY() + triangleHeight, 0.0f, Color::ORANGE);
	triangle1.CreateTriangle(v1, v2, v3);
	movementSpeed = 1.0f;
	maxMovement = v3.GetPosY();
	minMovement = screenHeight - v3.GetPosY();
	triangle1Position = v3.GetPosY() - triangleHeight / 2;


	Vertex v4 = Vertex(screenWidth / 2 - 300, screenHeight / 2 - triangleHeight / 2, 0.0f, Color::RED);
	Vertex v5 = Vertex(v4.GetPosX() + triangleWidth, v4.GetPosY(), 0.0f, Color::RED);
	Vertex v6 = Vertex(v4.GetPosX() + triangleWidth / 2, v4.GetPosY() + triangleHeight, 0.0f, Color::RED);
	triangle2.CreateTriangle(v4, v5, v6);
	movementSpeed = 1.0f;

	float heightOffset = 30;
	Vertex v7 = Vertex(screenWidth / 2 - 300, screenHeight / 2 + triangleHeight / 2 - heightOffset, 0.0f, Color::RED);
	Vertex v8 = Vertex(v7.GetPosX() + triangleWidth, v7.GetPosY(), 0.0f, Color::RED);
	Vertex v9 = Vertex(v7.GetPosX() + triangleWidth / 2, v7.GetPosY() - triangleHeight, 0.0f, Color::RED);
	triangle3.CreateTriangle(v7, v8, v9);
	initialRotationSpeed = 1.0f;
	currentRotationSpeed = initialRotationSpeed;
	rotationSpeedChange = 0.01f;
	maxRotationSpeed = 7.0f;


	Vertex v10 = Vertex(screenWidth / 2 - squareWidth / 2, screenHeight / 2 + squareHight / 2, 0.0f, Color::PINK);
	square.CreateSquare(v10, squareWidth, squareHight);

	squareWidth = 100;
	squareHight = 100;
	maxScale = 3.0f;
	minScale = 1.0f;
	currentScale = minScale;
	scaleChangeSpeed = 0.01f;
}

void Game::Update()
{
	triangle1Position += movementSpeed;
	triangle1.Translate(0.0f, movementSpeed, 0.0f);
	if (triangle1Position >= maxMovement || triangle1Position <= minMovement)
	{
		triangle1.Rotate(0.0f, 0.0f, 180.0f);
		movementSpeed *= -1;
	}

	currentRotationSpeed += rotationSpeedChange;
	if (currentRotationSpeed >= maxRotationSpeed || currentRotationSpeed <= initialRotationSpeed)
		rotationSpeedChange *= -1;
	std::cout << "Current rotation speed: " << currentRotationSpeed << std::endl;
	triangle2.Rotate(0.0f, 0.0f, currentRotationSpeed);
	triangle3.Rotate(0.0f, 0.0f, -currentRotationSpeed);

	currentScale += scaleChangeSpeed;
	if (currentScale >= maxScale - minScale || currentScale <= minScale)
		scaleChangeSpeed *= -1;

	float scaleModifier = minScale + scaleChangeSpeed;
	square.Scale(scaleModifier, scaleModifier, 0.0f);

	triangle1.Draw();
	triangle2.Draw();
	triangle3.Draw();
	square.Draw();
}

void Game::DeInitGame()
{

}
