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


Sprite rock = Sprite();
Animation rockSprite;

Sprite knuckles = Sprite();
Animation push;
Animation walkRight;
Animation idle;
Animation spin;

static const float screenWidth = 720.0f;
static const float screenHeight = 640.0f;

float rockWidth = 130;
float rockHeight = 100;


float speed = 0.5f;
float posChangeX = 0;
float posChangeY = 0;

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
	rock.SetTexture("Rock.jfif", 244, 207);
	glm::vec3 position1 = { 600.0f, 300.0f, 0.0f };
	rockSprite.AddFrames(76, 130, 82, 56, 244, 207, 1, 1);
	rock.CreateSquare(position1, rockWidth, rockHeight);
	rock.SetAnimation(&rockSprite);

	knuckles.SetTexture("Knuckles_Sprite_Sheet.png", 646, 473);
	glm::vec3 position = { 300.0f, 300.0f, 0.0f };

	walkRight.AddFrames(335, 384, 40, 42, 646, 473, 0.4f, 4);
	idle.AddFrames(0, 430.5f, 36, 42, 646, 473, 1, 1);
	push.AddFrames(422, 341, 37, 40, 646, 473, 1, 4);
	spin.AddFrames(0, 311, 32, 34, 646, 473, 0.3f, 6);

	knuckles.CreateSquare(position, 150.0f, 200.0f);
	knuckles.SetAnimation(&idle);

}

void Game::Update()
{
	deltaTime = MyClock::GetDeltaTime();

	posChangeX = 0.0f;
	posChangeY = 0.0f;

	KeepOnScreen(knuckles);

	if (Input::IsKeyDown(Key::A))
	{
		ChangeAnimation(knuckles, walkRight);
		posChangeX = -speed * deltaTime;
		knuckles.SetRotation(0.0f, 0.0f, 0.0f);
	}

	if (Input::IsKeyDown(Key::D))
	{
		knuckles.SetRotation(0.0f, 180.0f, 0.0f);
		posChangeX = speed * deltaTime;
		ChangeAnimation(knuckles, walkRight);
	}

	if (Input::IsKeyDown(Key::SPACE))
	{
		ChangeAnimation(knuckles, spin);
	}

	if (Input::IsKeyReleased(Key::D) || Input::IsKeyReleased(Key::A) || Input::IsKeyReleased(Key::SPACE))
	{
		ChangeAnimation(knuckles, idle);
	}

	if (Input::IsKeyReleased(Key::D) || Input::IsKeyReleased(Key::A))
	{
		ChangeAnimation(knuckles, idle);
	}

	if (collisionManager.CheckCollision(&knuckles, &rock))
	{
		//Funciona pero se "rompe la animacion", pueden probarlo
		//rock.SetPosition(rock.GetPosition().x + posChangeX, rock.GetPosition().y + posChangeY, 0); 
		ChangeAnimation(knuckles, push);
	}


	knuckles.Update();

	knuckles.SetPosition(knuckles.GetPosition().x + posChangeX, knuckles.GetPosition().y + posChangeY, 0);

	knuckles.Draw();
	rock.Draw();
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
