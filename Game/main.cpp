#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "sprite/Sprite.h"
#include "BaseGame.h"
#include "window/Window.h"
#include "input/Input.h"
#include "clock/Clock.h"
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

float posChangeX = 0;
float posChangeY = 0;
float posChangeZ = 0;

Animation walkUp;
Animation walkRight;

Animation* currentAnim;

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
	glm::vec3 position = { 300.0f, 300.0f, 0.0f };

	walkUp.AddFrames(0, 256, 64, 64, 256, 256, 1, 4);
	walkRight.AddFrames(0, 128, 64, 64, 256, 256, 1, 4);

	squareAnim.CreateSquare(position, 200.0f, 200.0f);
	squareAnim.SetAnimation(&walkRight);
}

void Game::Update()
{
	float deltaTime = MyClock::GetDeltaTime();

	//posChangeX = 0.0f;
	//posChangeY = 0.0f;
	//triangle1.SetRotatation(0.0f, 0.0f, rotation);

	//Multiplicar pos change por deltatime
	if (Input::IsKeyDown(Key::A))
		posChangeX -= 0.01 * deltaTime;

	if (Input::IsKeyDown(Key::D))
	{
		posChangeX += 0.01 * deltaTime;

		currentAnim = &walkRight;

		if (squareAnim.GetAnimation() != currentAnim)
			squareAnim.SetAnimation(currentAnim);

	}

	if (Input::IsKeyDown(Key::W))
	{
		posChangeY += 0.01 * deltaTime;

		currentAnim = &walkUp;

		if (squareAnim.GetAnimation() != currentAnim)
			squareAnim.SetAnimation(currentAnim);

	}

	if (Input::IsKeyDown(Key::S))
		posChangeY -= 0.01 * deltaTime;

	if (Input::IsKeyDown(Key::Q))
		posChangeZ += 0.01 * deltaTime;

	if (Input::IsKeyDown(Key::E))
		posChangeZ -= 0.01 * deltaTime;

	squareAnim.GetAnimation()->Update();

	squareAnim.SetPosition(squareAnim.GetPosition().x + posChangeX, squareAnim.GetPosition().y + posChangeY, 0);

	//squareAnim.SetRotation(squareAnim.GetRotation().x + posChangeX, squareAnim.GetRotation().y + posChangeY, squareAnim.GetRotation().z + posChangeZ);

	//cout << "Position: " << squareAnim.GetPosition().x << ", " << squareAnim.GetPosition().y << ", " << squareAnim.GetPosition().z << endl;

	squareAnim.Update();
	squareAnim.Draw();
}

void Game::DeInitGame()
{

}
