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

Shape square = Shape();
Shape square2 = Shape();
Shape debugAABB = Shape();

//Sprite square = Sprite();
Sprite Samus = Sprite();

static const float screenWidth = 720.0f;
static const float screenHeight = 640.0f;

float sWidth = 100;
float sHeight = 100;
float sX = 0;
float sY = screenHeight - sHeight;

float square2Width = 400.0f;

float posChangeX = 0;
float squarePosChangex = 0;
float scalex = 0;
float scaley = 0;
float rotationChangeZ = 0;

bool borderCollide = false;

Animation idle;
Animation walkLeft;

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

	/*square.SetTexture("texture.jpg", 301, 167);
	glm::vec3 position1 = { 600.0f, 600.0f, 0.0f };
	square.CreateSquare(position1, sWidth, sHeight);*/

	Samus.SetTexture("Samus Aran Sprite Sheet.png", 860, 762);
	glm::vec3 position = { 300.0f, 300.0f, 0.5f };

	idle.AddFrame(35, 655, 50, 70, 860, 762, 1);
	walkLeft.AddFrames(0, 480, 84, 70, 860, 762, 1, 20);

	Samus.CreateSquare(position, 200.0f, 200.0f);
	Samus.SetAnimation(&idle);

	square.CreateSquare(glm::vec3(100.0f, 300.0f, 0.5f), 100.0f, 100.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	square2.CreateSquare(glm::vec3(0.0f, 0.0f, 0.1f), square2Width, 400.0f, glm::vec4(0.0f, 0.0f, 1.0f, 0.2f));
}

void Game::Update()
{
	float deltaTime = MyClock::GetDeltaTime();

	float speed = 0.5f;
	float rotationSpeed = 0.1f;

	posChangeX = 0.0f;
	scalex = 0.0f;	
	rotationChangeZ = 0.0f;

	if (Samus.GetX() - sWidth / 2 > screenWidth)
	{
		Samus.SetX(-sWidth / 2);
	}
	if (Samus.GetX() + sWidth / 2 < 0)
	{
		Samus.SetX(screenWidth + sWidth / 2);
	}

	//triangle1.SetRotatation(0.0f, 0.0f, rotation);

	if (Input::IsKeyReleased(Key::A))
	{
		currentAnim = &idle;

		if (Samus.GetAnimation() != currentAnim)
			Samus.SetAnimation(currentAnim);
	}

	//Multiplicar pos change por deltatime
	if (Input::IsKeyDown(Key::A))
	{
		posChangeX = -speed * deltaTime;

		currentAnim = &walkLeft;

		if (Samus.GetAnimation() != currentAnim)
			Samus.SetAnimation(currentAnim);
	}

	/*if (Input::IsKeyDown(Key::D))
	{
		posChangeX = speed * deltaTime;

		currentAnim = &walkRight;

		if (Samus.GetAnimation() != currentAnim)
			Samus.SetAnimation(currentAnim);
	}*/

	/*if (Input::IsKeyDown(Key::W))
	{
		posChangeY = speed * deltaTime;

		currentAnim = &walkUp;

		if (Samus.GetAnimation() != currentAnim)
			Samus.SetAnimation(currentAnim);
	}*/

	if (Input::IsKeyDown(Key::S))
	{
		scalex = -speed * deltaTime;
		scaley = -speed * deltaTime;
	}

	if (Input::IsKeyDown(Key::W))
	{
		scalex = speed * deltaTime;
		scaley = speed * deltaTime;
	}

	if (Input::IsKeyDown(Key::Q))
	{
		rotationChangeZ = -rotationSpeed * deltaTime;
	}

	if (Input::IsKeyDown(Key::E))
	{
		rotationChangeZ = rotationSpeed * deltaTime;
	}

	if (square2.GetX() > screenWidth - square2Width/2)
	{
		borderCollide = true;
	}

	if (square2.GetX() < 0 + square2Width / 2)
	{
		borderCollide = false;
	}

	if (borderCollide)
	{
		squarePosChangex = -speed * deltaTime;
	}
	else
	{
		squarePosChangex = speed * deltaTime;
	}


	Samus.Update();

	Samus.SetPosition(Samus.GetPosition().x + posChangeX, Samus.GetPosition().y, 0.0f);

	if (collisionManager.CheckCollision(&Samus, &square))
		collisionManager.ResolveCollisionPush(&Samus, &square, 2.0f);

	square.SetScale(square.GetScale().x + scalex, square.GetScale().y + scaley, 0.0f);
	square.SetRotation(0.0f, 0.0f, square.GetRotation().z + rotationChangeZ);

	square2.SetPosition(square2.GetPosition().x + squarePosChangex, square.GetPosition().y, 0.0f);

	Samus.Draw();

	//debugAABB.SetPosition(Samus.GetPosition());
	//debugAABB.SetScale(collisionManager.GetCollisionWidthRotated(&Samus), collisionManager.GetCollisionHeightRotated(&Samus), 1.0f);

	square.Draw();
	square2.Draw();
	//debugAABB.Draw();
	//triangle1.Draw();
}

void Game::DeInitGame()
{

}
