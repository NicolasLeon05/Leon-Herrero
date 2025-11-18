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
Sprite knucles = Sprite();

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

Animation idle;

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

	knucles.SetTexture("Knuckles_Sprite_Sheet.png", 646, 473);
	glm::vec3 position = { 300.0f, 300.0f, 0.0f };

	idle.AddFrame(0, 420, 40, 40, 646, 473, 1);

	walkRight.AddFrames(0, 390, 37.4, 40, 646, 473, 1, 3);
	walkUp.AddFrames(0, 180, 37.4, 45, 646, 473, 1, 8);

	knucles.CreateSquare(position, 200.0f, 200.0f);
	knucles.SetAnimation(&idle);

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

	if (knucles.GetX() - sWidth / 2 > screenWidth)
	{
		knucles.SetX(-sWidth / 2);
	}
	if (knucles.GetX() + sWidth / 2 < 0)
	{
		knucles.SetX(screenWidth + sWidth / 2);
	}

	//triangle1.SetRotatation(0.0f, 0.0f, rotation);

	//Multiplicar pos change por deltatime
	if (Input::IsKeyDown(Key::A))
		posChangeX = -speed * deltaTime;

	if (Input::IsKeyDown(Key::D))
	{
		posChangeX = speed * deltaTime;

		currentAnim = &walkRight;

		if (knucles.GetAnimation() != currentAnim)
			knucles.SetAnimation(currentAnim);
	}

	if (Input::IsKeyDown(Key::W))
	{
		posChangeY = speed * deltaTime;

		currentAnim = &walkUp;

		if (knucles.GetAnimation() != currentAnim)
			knucles.SetAnimation(currentAnim);
	}

	if (Input::IsKeyDown(Key::S))
		posChangeY = -speed * deltaTime;

	if (Input::IsKeyDown(Key::Q))
		rotationChangeZ = -rotationSpeed * deltaTime;

	if (Input::IsKeyDown(Key::E))
		rotationChangeZ = rotationSpeed * deltaTime;

	knucles.Update();

	knucles.SetPosition(knucles.GetPosition().x + posChangeX, knucles.GetPosition().y + posChangeY, 0);

	if (collisionManager.CheckCollision(&knucles, &square))
		collisionManager.ResolveCollisionPush(&knucles, &square, 2.0f);

	if (collisionManager.CheckCollision(&knucles, &triangle1))
		collisionManager.ResolveCollisionPush(&knucles, &triangle1, 2.0f);

	knucles.SetRotation(0.0f, 0.0f, knucles.GetRotation().z + rotationChangeZ);

	cout << "Rotation: " << knucles.GetRotation().x << ", " << knucles.GetRotation().y << ", " << knucles.GetRotation().z << endl;

	knucles.Draw();

	debugAABB.SetPosition(knucles.GetPosition());
	debugAABB.SetScale(collisionManager.GetCollisionWidthRotated(&knucles), collisionManager.GetCollisionHeightRotated(&knucles), 1.0f);

	square.Draw();
	debugAABB.Draw();
	triangle1.Draw();
}

void Game::DeInitGame()
{

}
