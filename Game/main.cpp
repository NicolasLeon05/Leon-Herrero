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


static const float screenWidth = 720.0f;
static const float screenHeight = 640.0f;

Shape redSquare = Shape();
Shape pinkSquare = Shape();
Shape orangeTriangle = Shape();
float shapeWidth = 100.0f;
float shapeHeight = 100.0f;
float scaleMultiplier = 1;
float scaleSpeed = 0.002f;

glm::vec3 maxScale;
glm::vec3 startScale;

glm::vec3 trianglePosition = { screenWidth - shapeWidth, screenHeight / 2, 0 };
glm::vec3 pinkSquarePosition = { screenWidth / 2, screenHeight / 2, 0 };


glm::vec3 target1 = { screenWidth - shapeWidth / 2, screenHeight - shapeHeight / 2, 0 };
glm::vec3 target2 = { screenWidth - shapeWidth / 2, shapeHeight / 2, 0 };
glm::vec3 target3 = { shapeWidth / 2, shapeHeight / 2, 0 };
glm::vec3 target4 = { shapeWidth / 2, screenHeight - shapeHeight / 2, 0 };

int stepsRedSquare = 0;
int stepsOrangeTriangle = 0;
int stepsPinkSquare = 0;


//Ejercicio 4
Shape redTriA;
Shape redTriB;

static float triRotSpeed = 0.01f;
static float triRotSpeedMin = 0.01f;
static float triRotSpeedMax = 0.1f;
static float triRotSpeedModifier = 0.002f;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}

void Game::InitGame()
{
	redSquare.CreateSquare(target4, shapeWidth, shapeHeight, { 0,0,1,1 });
	pinkSquare.CreateSquare(pinkSquarePosition, shapeWidth / 2, shapeHeight / 2, { 1,0.55f,0.71f,1 });
	orangeTriangle.CreateTriangle(trianglePosition, shapeWidth, shapeHeight, { 1, 0.65f, 0, 1 });

	maxScale = { pinkSquare.GetScale().x * 3,  pinkSquare.GetScale().y * 3, pinkSquare.GetScale().z * 3 };
	startScale = { pinkSquare.GetScale().x,  pinkSquare.GetScale().y, pinkSquare.GetScale().z };

	//Ejercicio 4
	glm::vec3 starPos = { screenWidth * 0.25f, screenHeight * 0.5f, 0 };

	redTriA.CreateTriangle(starPos, shapeWidth, shapeHeight, { 1,0,0,1 });
	redTriB.CreateTriangle(starPos, shapeWidth, shapeHeight, { 1,0,0,1 });

	redTriB.SetRotation(0, 0, 180);
}

void Game::Update()
{
	float deltaTime = MyClock::GetDeltaTime();

	float mov = 0.5f * deltaTime;
	float movMargin = 3;

	float movSpeedX = 0;
	float movSpeedY = 0;

	float rotSpeed = 0.5f * deltaTime;

	switch (stepsRedSquare)
	{
	case 0:
	{
		if (redSquare.GetPosition().x - target1.x > movMargin || target1.x - redSquare.GetPosition().x > movMargin)
			movSpeedX = (redSquare.GetPosition().x < target2.x) ? mov : -mov;
		else
			stepsRedSquare++;
		break;
	}

	case 1:
	{
		if (redSquare.GetPosition().y - target2.y > movMargin || target2.y - redSquare.GetPosition().y > movMargin)
			movSpeedY = (redSquare.GetPosition().y > target1.y) ? mov : -mov;
		else
			stepsRedSquare++;
		break;
	}

	case 2:
	{
		if (redSquare.GetPosition().x - target3.x > movMargin || target3.x - redSquare.GetPosition().x > movMargin)
			movSpeedX = (redSquare.GetPosition().x > target4.x) ? -mov : mov;
		else
			stepsRedSquare++;

		break;
	}

	case 3:
	{
		if (redSquare.GetPosition().y - target4.y > movMargin || target4.y - redSquare.GetPosition().y > movMargin)
			movSpeedY = (redSquare.GetPosition().y < target1.y) ? mov : -mov;
		else
			stepsRedSquare++;
		break;
	}

	default:
		stepsRedSquare = 0;
		break;
	}

	redSquare.SetPosition(redSquare.GetPosition().x + movSpeedX, redSquare.GetPosition().y + movSpeedY, redSquare.GetPosition().z);
	redSquare.SetRotation(redSquare.GetRotation().x, redSquare.GetRotation().y, redSquare.GetRotation().z - rotSpeed);

	movSpeedY = 0;
	switch (stepsOrangeTriangle)
	{
	case 0:
	{
		if (orangeTriangle.GetPosition().y - screenHeight - shapeHeight / 2 > movMargin || screenHeight - shapeHeight / 2 - orangeTriangle.GetPosition().y > movMargin)
			movSpeedY = mov;
		else
		{
			stepsOrangeTriangle++;
			orangeTriangle.SetRotation(orangeTriangle.GetRotation().x, orangeTriangle.GetRotation().y, 180);
		}
		break;
	}

	case 1:
	{
		if (orangeTriangle.GetPosition().y - shapeHeight / 2 > movMargin || shapeHeight / 2 - orangeTriangle.GetPosition().y > movMargin)
			movSpeedY = -mov;
		else
		{
			stepsOrangeTriangle++;
			orangeTriangle.SetRotation(orangeTriangle.GetRotation().x, orangeTriangle.GetRotation().y, 0);
		}
		break;
	}

	default:
	{
		stepsOrangeTriangle = 0;
		break;
	}
	}

	orangeTriangle.SetPosition(orangeTriangle.GetPosition().x, orangeTriangle.GetPosition().y + movSpeedY, orangeTriangle.GetPosition().z);


	scaleMultiplier += scaleSpeed * deltaTime;

	if (scaleMultiplier > 3.0f)
	{
		scaleMultiplier = 3.0f;
		scaleSpeed = -fabs(scaleSpeed);
	}
	else if (scaleMultiplier < 1.0f)
	{
		scaleMultiplier = 1.0f;
		scaleSpeed = fabs(scaleSpeed);
	}


	pinkSquare.SetScale(startScale.x * scaleMultiplier, startScale.y * scaleMultiplier, 0);

	triRotSpeed += triRotSpeedModifier * deltaTime;

	if (triRotSpeed > triRotSpeedMax)
	{
		triRotSpeed = triRotSpeedMax;
		triRotSpeedModifier = -fabs(triRotSpeedModifier);
	}
	else if (triRotSpeed < triRotSpeedMin)
	{
		triRotSpeed = triRotSpeedMin;
		triRotSpeedModifier = fabs(triRotSpeedModifier);
	}

	cout << "Delta time: " << deltaTime << endl;

	redTriA.SetRotation(
		redTriA.GetRotation().x,
		redTriA.GetRotation().y,
		redTriA.GetRotation().z + triRotSpeed
	);

	redTriB.SetRotation(
		redTriB.GetRotation().x,
		redTriB.GetRotation().y,
		redTriB.GetRotation().z - triRotSpeed
	);



	redSquare.Draw();
	orangeTriangle.Draw();
	pinkSquare.Draw();
	redTriA.Draw();
	redTriB.Draw();
}

void Game::DeInitGame()
{

}
