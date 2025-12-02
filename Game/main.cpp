#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "sprite/Sprite.h"
#include "BaseGame.h"
#include "window/Window.h"
#include "input/Input.h"
#include "clock/Clock.h"
#include "glm.hpp"


void ChangeAnimation(Sprite& sprite, Animation& animation);
void KeepOnScreen(Entity2D& entity);

class Game : public BaseGame
{
public:

	void InitGame() override;
	void Update() override;
	void DeInitGame() override;
};


//Sprite rock = Sprite();
//Animation rockSprite;
static const float screenWidth = 720.0f;
static const float screenHeight = 640.0f;

Sprite samus = Sprite();
Animation push;
Animation walkLeft;
Animation idle;
Animation spin;

Shape square = Shape();
Shape square2 = Shape();
float rotationDelta = 50.0f;
float scaleDelta = 50.0f;

//float rockWidth = 130;
//float rockHeight = 100;


float speed = 200.0f;
float posChangeX = 0;
float posChangeY = 0;
float moveX = 0;
float moveY = 0;
float deltaTime;

Animation* currentAnim;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{
	//rock.SetTexture("Rock.jfif", 244, 207);
	//glm::vec3 position1 = { 600.0f, 300.0f, 0.0f };
	//rockSprite.AddFrames(76, 130, 82, 56, 244, 207, 1, 1);
	//rock.CreateSquare(position1, rockWidth, rockHeight);
	//rock.SetAnimation(&rockSprite);

	samus.SetTexture("Samus Aran Sprite Sheet.png", 860, 762);
	glm::vec3 samusPosition = { 300.0f, 300.0f, 0.0f };

	walkLeft.AddFrames(20, 482, 82, 75, 860, 762, 0.4f, 10);
	idle.AddFrame(20, 652, 75, 75, 860, 762, 1);
	//push.AddFrames(422, 341, 37, 40, 860, 762, 1, 4);
	//spin.AddFrames(0, 311, 32, 34, 860, 762, 0.3f, 6);

	samus.CreateSquare(samusPosition, 100.0f, 150.0f);
	samus.SetAnimation(&idle);

	glm::vec3 squarePosition = { 100, screenHeight / 2, 0.0f };
	square.CreateSquare(squarePosition, 100, 100, { 1, 0, 0, 1 });
	square2.CreateSquare(squarePosition, 300, 300, { 0, 0, 1, 0.5f });

}

void Game::Update()
{
	deltaTime = MyClock::GetDeltaTime() / 1000;
	cout << deltaTime << endl;

	posChangeX = 0.0f;
	posChangeY = 0.0f;
	moveX = 0;
	moveY = 0;

	KeepOnScreen(samus);
	//KeepOnScreen(rock);

	if (Input::IsKeyDown(Key::A))
	{
		ChangeAnimation(samus, walkLeft);
		posChangeX = -speed * deltaTime;
		samus.SetRotation(0.0f, 0.0f, 0.0f);
	}

	if (Input::IsKeyDown(Key::D))
	{
		samus.SetRotation(0.0f, 180.0f, 0.0f);
		posChangeX = speed * deltaTime;
		ChangeAnimation(samus, walkLeft);
	}

	if (Input::IsKeyDown(Key::SPACE))
		ChangeAnimation(samus, spin);

	if (Input::IsKeyUp(Key::D) && Input::IsKeyUp(Key::A) && Input::IsKeyUp(Key::SPACE))
		ChangeAnimation(samus, idle);

	if (Input::IsKeyDown(Key::LEFT))
		square.SetRotation(
			square.GetRotation().x,
			square.GetRotation().y,
			square.GetRotation().z + rotationDelta * deltaTime);

	if (Input::IsKeyDown(Key::RIGHT))
		square.SetRotation(
			square.GetRotation().x,
			square.GetRotation().y,
			square.GetRotation().z - rotationDelta * deltaTime);

	if (Input::IsKeyDown(Key::UP))
		square.SetScale(
			square.GetScale().x + scaleDelta * deltaTime,
			square.GetScale().y + scaleDelta * deltaTime,
			square.GetScale().z);

	if (Input::IsKeyDown(Key::DOWN))
		square.SetScale(
			square.GetScale().x - scaleDelta * deltaTime,
			square.GetScale().y - scaleDelta * deltaTime,
			square.GetScale().z);

	if (Input::IsKeyDown(Key::I))
		moveY = speed * deltaTime;

	if (Input::IsKeyDown(Key::J))
		moveX = -speed * deltaTime;

	if (Input::IsKeyDown(Key::K))
		moveY = -speed * deltaTime;

	if (Input::IsKeyDown(Key::L))
		moveX = speed * deltaTime;

	if (collisionManager.CheckCollision(&samus, &square))
		collisionManager.ResolveCollisionPush(&samus, &square);
	//if (collisionManager.CheckCollision(&knuckles, &rock))
	//{
	//	//Funciona pero se "rompe la animacion", pueden probarlo
	//	//rock.SetPosition(rock.GetPosition().x + posChangeX, rock.GetPosition().y + posChangeY, 0);
	//	ChangeAnimation(knuckles, push);
	//}

	samus.Update();

	if (posChangeX != 0 || posChangeY != 0)
		samus.SetPosition(samus.GetPosition().x + posChangeX, samus.GetPosition().y + posChangeY, 0);

	if (moveX != 0 || moveY != 0)
		square2.SetPosition(square2.GetPosition().x + moveX, square2.GetPosition().y + moveY, 0);

	square2.Draw();
	samus.Draw();
	square.Draw();
	//rock.Draw();
}

void Game::DeInitGame()
{

}


void ChangeAnimation(Sprite& sprite, Animation& animation)
{
	currentAnim = &animation;

	if (sprite.GetAnimation() != currentAnim)
		sprite.SetAnimation(currentAnim);
}

void KeepOnScreen(Entity2D& entity)
{
	if (entity.GetX() - entity.GetScale().x / 2 > screenWidth)
	{
		entity.SetX(-entity.GetScale().x / 2);
	}
	if (entity.GetX() + entity.GetScale().x / 2 < 0)
	{
		entity.SetX(screenWidth + entity.GetScale().x / 2);
	}
}
