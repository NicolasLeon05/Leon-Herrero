#include "vertex/Color.h"
#include "vertex/Vertex.h"
#include "shape/Shape.h"
#include "sprite/Sprite.h"
#include "BaseGame.h"
#include "window/Window.h"
#include "input/Input.h"
#include "clock/Clock.h"
#include "tilemap/Tilemap.h"
#include "glm.hpp"


class Game : public BaseGame
{
public:

	void InitGame() override;
	void Update() override;
	void DeInitGame() override;
};


static const float screenWidth = 320.0f * 2.5f;
static const float screenHeight = 320.0f * 2.5f;

TileMap tileMap;
Sprite player;
Animation animation;

static const float playerWidth = 30.0f;
static const float playerHeight = 36.0f;
static const float playerSpeed = 0.1f;

float scaledTileWidth;
float scaledTileHeight;
float speedLimitCounter;

void main()
{
	Window window = Window(screenWidth, screenHeight, "Engine");
	Game game;

	game.RunEngine(window);
}


void Game::InitGame()
{
	speedLimitCounter = 0.0f;

	float mapWidth = 20.0f * 16.0f; //320
	float mapHeight = 20.0f * 16.0f; //320

	tileMap.SetScale(screenWidth / mapWidth, screenHeight / mapHeight, 1.0f);
	float mapX = (screenWidth - mapWidth * tileMap.GetScale().x) * 0.5f;
	float mapY = (screenHeight - mapHeight * tileMap.GetScale().y) * 0.5f;
	tileMap.SetPosition(mapX, mapY, 0.0f);

	bool loaded = tileMap.Load("Assets/TileMap/TestFinal/tilemap.tmx");

	if (!loaded)
	{
		std::cout << "Tilemap loading failed" << std::endl;
	}
	else
	{
		std::cout << "Tilemap loaded correctly" << std::endl;
		std::cout << "Map size: "
			<< tileMap.GetWidth()
			<< " x "
			<< tileMap.GetHeight()
			<< std::endl;

		std::cout << "Tile size: "
			<< tileMap.GetTileWidth()
			<< " x "
			<< tileMap.GetTileHeight()
			<< std::endl;
	}

	scaledTileWidth = static_cast<float>(tileMap.GetTileWidth()) * tileMap.GetScale().x;
	scaledTileHeight = static_cast<float>(tileMap.GetTileHeight()) * tileMap.GetScale().y;

	int startColumn = 12;
	int startRow = 8;

	float playerX = tileMap.GetX() + (static_cast<float>(startColumn) + 0.5f) * scaledTileWidth;
	float playerY = tileMap.GetY() + (static_cast<float>(tileMap.GetHeight()) - static_cast<float>(startRow) - 0.5f) * scaledTileHeight;

	player.SetTexture("Assets/TileMap/TestFinal/tilemap.png", 305.0f, 186.0f);
	player.CreateSquare(glm::vec3(playerX, playerY, 0.0f), playerWidth, playerHeight);

	animation.AddFrames(84.5f, 17.0f, 17.0f, 16.0f, 305.0f, 186.0f, 5.0f, 7);
	player.SetAnimation(&animation);
}

void Game::Update()
{
	float deltaTimeInSeconds = MyClock::GetDeltaTime() / 1000;

	speedLimitCounter += deltaTimeInSeconds;

	if (speedLimitCounter >= 0.1f)
	{
		float movementX = 0.0f;
		float movementY = 0.0f;

		if (Input::IsKeyDown(Key::W))
			movementY = scaledTileHeight;
		else if (Input::IsKeyDown(Key::S))
			movementY = -scaledTileHeight;
		else if (Input::IsKeyDown(Key::A))
			movementX = -scaledTileWidth;
		else if (Input::IsKeyDown(Key::D))
			movementX = scaledTileWidth;

		if (movementX != 0.0f || movementY != 0.0f)
		{
			player.SetPosition(player.GetX() + movementX, player.GetY() + movementY, player.GetZ());

			if (tileMap.CheckCollision(player))
				std::cout << "Tile collision" << std::endl;

			speedLimitCounter = 0.0f;
		}
	}

	tileMap.Update();
	player.Update();

	tileMap.Draw();
	player.Draw();
}

void Game::DeInitGame()
{
	tileMap.Unload();
}
