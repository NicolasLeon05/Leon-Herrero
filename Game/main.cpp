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

CollisionManager* colManager;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void ResolveCollisionPush(Entity2D* entity, Entity2D* other, float margin = 0.0f)
{
	float halfW1 = colManager->GetCollisionWidthRotated(entity) * 0.5f;
	float halfH1 = colManager->GetCollisionHeightRotated(entity) * 0.5f;

	float halfW2 = colManager->GetCollisionWidthRotated(other) * 0.5f;
	float halfH2 = colManager->GetCollisionHeightRotated(other) * 0.5f;

	glm::vec3 pos1 = entity->GetPosition();
	glm::vec3 pos2 = other->GetPosition();

	float dx = pos1.x - pos2.x;
	float px = (halfW1 + halfW2) - fabs(dx);

	float dy = pos1.y - pos2.y;
	float py = (halfH1 + halfH2) - fabs(dy);

	if (px <= 0 || py <= 0)
		return;

	if (px < py)
	{
		if (dx > 0)
			entity->SetX(pos1.x + px + margin);
		else
			entity->SetX(pos1.x - px - margin);
	}
	else
	{
		if (dy > 0)
			entity->SetY(pos1.y + py + margin);
		else
			entity->SetY(pos1.y - py - margin);
	}
}

void Game::InitGame()
{
	colManager = &collisionManager;

	debugAABB.CreateSquare(glm::vec3(0, 0, 0), 200.0f, 200.0f, glm::vec4(1, 0, 0, 0.2f));

	square.SetTexture("texture.jpg", 301, 167);
	glm::vec3 position1 = { 600.0f, 600.0f, 0.0f };
	square.CreateSquare(position1, sWidth, sHeight);

	squareAnim.SetTexture("pokemon.png", 256, 256);
	glm::vec3 position = { 300.0f, 300.0f, 0.0f };

	walkUp.AddFrames(0, 256, 64, 64, 256, 256, 1, 4);
	walkRight.AddFrames(0, 128, 64, 64, 256, 256, 1, 4);

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

	squareAnim.GetAnimation()->Update();

	squareAnim.SetPosition(squareAnim.GetPosition().x + posChangeX, squareAnim.GetPosition().y + posChangeY, 0);

	if (collisionManager.CheckCollision(&squareAnim, &square))
		ResolveCollisionPush(&squareAnim, &square, 2.0f);   // margen de 2px

	if (collisionManager.CheckCollision(&squareAnim, &triangle1))
		ResolveCollisionPush(&squareAnim, &triangle1, 2.0f);

	squareAnim.SetRotation(0.0f, 0.0f, squareAnim.GetRotation().z + rotationChangeZ);

	cout << "Rotation: " << squareAnim.GetRotation().x << ", " << squareAnim.GetRotation().y << ", " << squareAnim.GetRotation().z << endl;

	squareAnim.Update();
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
