#include "Game.h"

#include "input/Input.h"
#include "clock/Clock.h"
#include "glm.hpp"

#include <iostream>

const float Game::screenWidth = 320.0f * 2.5f;
const float Game::screenHeight = 320.0f * 2.5f;

const float Game::playerWidth = 30.0f;
const float Game::playerHeight = 36.0f;
const float Game::movementCooldown = 0.1f;

Game::Game()
{
	scaledTileWidth = 0.0f;
	scaledTileHeight = 0.0f;
	speedLimitCounter = 0.0f;
}

void Game::InitGame()
{
	InitializeTileMap();

	if (!tileMap.IsLoaded())
		return;

	InitializePlayer();
}

void Game::InitializeTileMap()
{
	float mapWidth = 20.0f * 16.0f;
	float mapHeight = 20.0f * 16.0f;
	tileMap.SetScale(screenWidth / mapWidth, screenHeight / mapHeight, 1.0f);

	float mapX = (screenWidth - mapWidth * tileMap.GetScale().x) * 0.5f;
	float mapY = (screenHeight - mapHeight * tileMap.GetScale().y) * 0.5f;
	tileMap.SetPosition(mapX, mapY, 0.0f);

	bool loaded = tileMap.Load("Assets/TileMap/TestFinal/tilemap.tmx");

	if (!loaded)
	{
		std::cout << "Tilemap loading failed" << std::endl;
		return;
	}

	std::cout << "Tilemap loaded correctly" << std::endl;
	std::cout << "Map size: " << tileMap.GetWidth() << " x " << tileMap.GetHeight() << std::endl;
	std::cout << "Tile size: " << tileMap.GetTileWidth() << " x " << tileMap.GetTileHeight() << std::endl;

	scaledTileWidth = static_cast<float>(tileMap.GetTileWidth()) * tileMap.GetScale().x;
	scaledTileHeight = static_cast<float>(tileMap.GetTileHeight()) * tileMap.GetScale().y;
}

void Game::InitializePlayer()
{
	const int startColumn = 12;
	const int startRow = 8;

	float playerX = tileMap.GetX() + (static_cast<float>(startColumn) + 0.5f) * scaledTileWidth;
	float playerY = tileMap.GetY() + (static_cast<float>(tileMap.GetHeight()) - static_cast<float>(startRow) - 0.5f) * scaledTileHeight;

	player.SetTexture("Assets/TileMap/TestFinal/tilemap.png", 305, 186);
	player.CreateSquare(glm::vec3(playerX, playerY, 0.0f), playerWidth, playerHeight);

	animation.AddFrames(84.5f, 17.0f, 17.0f, 16.0f, 305.0f, 186.0f, 5.0f, 7);
	player.SetAnimation(&animation);
}

void Game::Update()
{
	float deltaTimeInSeconds = MyClock::GetDeltaTime() / 1000.0f;

	UpdatePlayerMovement(deltaTimeInSeconds);

	tileMap.Update();
	player.Update();

	tileMap.Draw();
	player.Draw();
}

void Game::UpdatePlayerMovement(float deltaTime)
{
	speedLimitCounter += deltaTime;

	if (speedLimitCounter < movementCooldown)
		return;

	float movementX = 0.0f;
	float movementY = 0.0f;

	if (Input::IsKeyDown(Key::W))
	{
		movementY = scaledTileHeight;
	}
	else if (Input::IsKeyDown(Key::S))
	{
		movementY = -scaledTileHeight;
	}
	else if (Input::IsKeyDown(Key::A))
	{
		movementX = -scaledTileWidth;
	}
	else if (Input::IsKeyDown(Key::D))
	{
		movementX = scaledTileWidth;
	}

	if (movementX == 0.0f && movementY == 0.0f)
	{
		return;
	}

	player.SetPosition(player.GetX() + movementX, player.GetY() + movementY, player.GetZ());

	if (tileMap.CheckCollision(player))
		std::cout << "Tile collision" << std::endl;

	speedLimitCounter = 0.0f;
}

void Game::DeInitGame()
{
	tileMap.Unload();
}