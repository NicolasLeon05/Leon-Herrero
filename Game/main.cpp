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
Shape debugAABB = Shape();

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
float rotationChangeZ = 0;

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
	debugAABB.CreateSquare(glm::vec3(0, 0, 0), 200.0f, 200.0f, glm::vec4(1, 0, 0, 0.2f));

	square.SetTexture("texture.jpg", 301, 167);
	glm::vec3 position1 = { 600.0f, 600.0f, 0.0f };
	square.CreateSquare(position1, sWidth, sHeight);

	squareAnim.SetTexture("pokemon.png", 256, 256);
	glm::vec3 position = { 300.0f, 300.0f, 0.0f };

	walkUp.AddFrames(0, 256, 64, 64, 256, 256, 1, 4);
	walkRight.AddFrames(0, 192, 64, 64, 256, 256, 1, 4);

	squareAnim.CreateSquare(position, 200.0f, 200.0f);
	squareAnim.SetAnimation(&walkRight);

	triangle1.CreateTriangle(glm::vec3(10.0f, 10.0f, 0.0f), 100.0f, 100.0f, glm::vec4(0.5f, 0.0f, 0.5f, 1));
}

void Game::Update()
{
	float deltaTime = MyClock::GetDeltaTime();

	float speed = 0.5f;
	float rotationSpeed = 0.1f;

	posChangeX = 0.0f;
	posChangeY = 0.0f;	
	rotationChangeZ = 0.0f;

	if (squareAnim.GetX() - sWidth / 2 > screenWidth)
	{
		squareAnim.SetX(-sWidth / 2);
	}
	if (squareAnim.GetX() + sWidth / 2 < 0)
	{
		squareAnim.SetX(screenWidth + sWidth / 2);
	}

	//triangle1.SetRotatation(0.0f, 0.0f, rotation);

	//Multiplicar pos change por deltatime
	if (Input::IsKeyDown(Key::A))
		posChangeX = -speed * deltaTime;

	if (Input::IsKeyDown(Key::D))
	{
		posChangeX = speed * deltaTime;

		currentAnim = &walkRight;

		if (squareAnim.GetAnimation() != currentAnim)
			squareAnim.SetAnimation(currentAnim);
	}

	if (Input::IsKeyDown(Key::W))
	{
		posChangeY = speed * deltaTime;

		currentAnim = &walkUp;

		if (squareAnim.GetAnimation() != currentAnim)
			squareAnim.SetAnimation(currentAnim);
	}

	if (Input::IsKeyDown(Key::S))
		posChangeY = -speed * deltaTime;

	if (Input::IsKeyDown(Key::Q))
		rotationChangeZ = -rotationSpeed * deltaTime;

	if (Input::IsKeyDown(Key::E))
		rotationChangeZ = rotationSpeed * deltaTime;

	squareAnim.Update();

	squareAnim.SetPosition(squareAnim.GetPosition().x + posChangeX, squareAnim.GetPosition().y + posChangeY, 0);

	if (collisionManager.CheckCollision(&squareAnim, &square))
		collisionManager.ResolveCollisionPush(&squareAnim, &square, 2.0f);

	if (collisionManager.CheckCollision(&squareAnim, &triangle1))
		collisionManager.ResolveCollisionPush(&squareAnim, &triangle1, 2.0f);

	squareAnim.SetRotation(0.0f, 0.0f, squareAnim.GetRotation().z + rotationChangeZ);

	cout << "Rotation: " << squareAnim.GetRotation().x << ", " << squareAnim.GetRotation().y << ", " << squareAnim.GetRotation().z << endl;

	squareAnim.Draw();

	debugAABB.SetPosition(squareAnim.GetPosition());
	debugAABB.SetScale(collisionManager.GetCollisionWidthRotated(&squareAnim), collisionManager.GetCollisionHeightRotated(&squareAnim), 1.0f);

	square.Draw();
	debugAABB.Draw();
	triangle1.Draw();
}

void Game::DeInitGame()
{

}
