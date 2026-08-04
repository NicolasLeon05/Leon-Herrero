#include "Game.h"

#include "input/Input.h"
#include "clock/Clock.h"
#include "glm.hpp"

#include <iostream>

const float Game::screenWidth = 320.0f * 2.0f;
const float Game::screenHeight = 320.0f * 2.0f;


void ChangeAnimation(Sprite& sprite, Animation& animation);
Direction GetDirection(Key lastKey);

static Key lastKeyPressed;
static Direction bulletDirection;

Game::Game()
{
	scaledTileWidth = 0.0f;
	scaledTileHeight = 0.0f;
	bulletFired = false;
}

void Game::InitGame()
{
	InitializeTileMap();

	if (!tileMap.IsLoaded())
		return;

	InitializeEntities();
}

void Game::InitializeTileMap()
{
	float mapWidth = 20.0f * 16.0f; //Tile size in x * tiles in x axys
	float mapHeight = 20.0f * 16.0f;//Tile size in y * tiles in y axys
	tileMap.SetScale(screenWidth / mapWidth, screenHeight / mapHeight, 1.0f);

	float mapX = screenWidth - mapWidth * tileMap.GetScale().x;
	float mapY = screenHeight - mapHeight * tileMap.GetScale().y;
	tileMap.SetPosition(mapX, mapY, 0.0f);

	bool loaded = tileMap.Load("Assets/TileMap/Final/tilemap.tmx");

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

void Game::InitializeEntities()
{
	const int startColumn = 12;
	const int startRow = 8;

	float playerX = tileMap.GetX() + (static_cast<float>(startColumn) + 0.5f) * scaledTileWidth;
	float playerY = tileMap.GetY() + (static_cast<float>(tileMap.GetHeight()) - static_cast<float>(startRow) - 0.5f) * scaledTileHeight;

	player.SetTexture("Assets/TileMap/Final/NES - Battle City JPN - General Sprites.png", 400, 256);
	player.CreateSquare(glm::vec3(playerX, playerY, 0.0f), scaledTileWidth, scaledTileHeight);

	playerUp.AddFrames(0.0f, 240.0f, 16.0f, 15.0f, 400.0f, 256.0f, 0.2f, 2);
	playerDown.AddFrames(64.0f, 241.0f, 16.0f, 15.0f, 400.0f, 256.0f, 0.2f, 2);
	playerRight.AddFrames(95.0f, 240.0f, 16.0f, 15.0f, 400.0f, 256.0f, 0.2f, 2);
	playerLeft.AddFrames(32.0f, 240.0f, 16.0f, 15.0f, 400.0f, 256.0f, 0.2f, 2);

	player.SetAnimation(&playerUp);

	bulletSprite.SetTexture("Assets/TileMap/Final/NES - Battle City JPN - General Sprites.png", 400, 256);
	bulletSprite.CreateSquare(glm::vec3(playerX + 1, playerY, 0.0f), scaledTileWidth, scaledTileHeight);

	explosion.AddFrames(257.0f, 112.0f, 15.0f, 16.0f, 400.0f, 256.0f, 0.5f, 3);
	bulletSprite.SetScale(bulletSprite.GetScale().x / 2, bulletSprite.GetScale().y / 2, bulletSprite.GetScale().z);
	bulletUp.AddFrame(320.5f, 149.0f, 8.0f, 8.0f, 400.0f, 256.0f, 1.0f);
	bulletDown.AddFrame(336.5f, 149.0f, 8.0f, 8.0f, 400.0f, 256.0f, 1.0f);
	bulletRight.AddFrame(344.0f, 149.0f, 8.0f, 8.0f, 400.0f, 256.0f, 1.0f);
	bulletLeft.AddFrame(328.0f, 149.0f, 8.0f, 8.0f, 400.0f, 256.0f, 1.0f);

	bulletSprite.SetAnimation(&bulletLeft);

	bulletSprite = bulletSprite;
	bulletFired = false;
}

void Game::Update()
{
	float deltaTimeInSeconds = MyClock::GetDeltaTime() / 1000.0f;

	UpdatePlayerMovement(deltaTimeInSeconds);
	UpdateBulletMovement(deltaTimeInSeconds, 100.0f);

	tileMap.Update();
	player.Update();
	bulletSprite.Update();


	tileMap.Draw();
	player.Draw();

	//Explosion animation finished
	if (bulletSprite.GetAnimation() == &explosion && bulletSprite.GetAnimation()->HasAnimationFinished())
		bulletFired = false;
	else
		bulletSprite.Draw();


	//Draw(bullet);
}

void Game::UpdatePlayerMovement(float deltaTime)
{
	float movementX = 0.0f;
	float movementY = 0.0f;
	float movementSpeed = 75.0f * deltaTime;


	if (Input::IsKeyDown(Key::W))
	{
		movementY = movementSpeed;
		ChangeAnimation(player, playerUp);
		lastKeyPressed = Key::W;
	}
	else if (Input::IsKeyDown(Key::S))
	{
		movementY = -movementSpeed;
		ChangeAnimation(player, playerDown);
		lastKeyPressed = Key::S;
	}
	else if (Input::IsKeyDown(Key::A))
	{
		movementX = -movementSpeed;
		ChangeAnimation(player, playerLeft);
		lastKeyPressed = Key::A;
	}
	else if (Input::IsKeyDown(Key::D))
	{
		movementX = movementSpeed;
		ChangeAnimation(player, playerRight);
		lastKeyPressed = Key::D;
	}

	if (Input::IsKeyReleased(Key::SPACE))
	{
		if (bulletFired)
			return;

		bulletDirection = GetDirection(lastKeyPressed);
		SetBulletFirstMovement();
	}

	if (movementX == 0.0f && movementY == 0.0f)
		return;

	player.SetPosition(player.GetX() + movementX, player.GetY() + movementY, player.GetZ());
	//bulletSprite.SetPosition(bulletSprite.GetX() + movementX * 1.1f, bulletSprite.GetY() + movementY * 1.1f, bulletSprite.GetZ());

	bool playerCollidedWithMap = tileMap.CheckCollision(player);
}

void Game::SetBulletFirstMovement()
{
	float posX = player.GetPosition().x;
	float posY = player.GetPosition().y;
	float posZ = player.GetPosition().z;
	float playerHalfWidth = player.GetScale().x / 2;
	float playerHalfHeight = player.GetScale().y / 2;

	switch (bulletDirection)
	{
	case Direction::Up:
		ChangeAnimation(bulletSprite, bulletUp);
		bulletSprite.SetPosition(posX, posY + playerHalfHeight, posZ);
		break;
	case Direction::Down:
		ChangeAnimation(bulletSprite, bulletDown);
		bulletSprite.SetPosition(posX, posY - playerHalfHeight, posZ);
		break;
	case Direction::Right:
		ChangeAnimation(bulletSprite, bulletRight);
		bulletSprite.SetPosition(posX + playerHalfWidth, posY, posZ);
		break;
	case Direction::Left:
		ChangeAnimation(bulletSprite, bulletLeft);
		bulletSprite.SetPosition(posX - playerHalfWidth, posY, posZ);
		break;
	default:
		break;
	}

	bulletFired = true;
}

void Game::UpdateBulletMovement(float deltaTime, float speed)
{
	if (!bulletFired)
		return;

	float posX = bulletSprite.GetPosition().x;
	float posY = bulletSprite.GetPosition().y;
	float posZ = bulletSprite.GetPosition().z;

	speed *= deltaTime;

	switch (bulletDirection)
	{
	case Direction::Up:
		bulletSprite.SetPosition(posX, posY + speed, posZ);
		break;
	case Direction::Down:
		bulletSprite.SetPosition(posX, posY - speed, posZ);
		break;
	case Direction::Right:
		bulletSprite.SetPosition(posX + speed, posY, posZ);
		break;
	case Direction::Left:
		bulletSprite.SetPosition(posX - speed, posY, posZ);
		break;
	default:
		break;
	}

	if (tileMap.CheckCollision(bulletSprite))
		ChangeAnimation(bulletSprite, explosion);
}

void Game::DeInitGame()
{
	tileMap.Unload();
}

void ChangeAnimation(Sprite& sprite, Animation& animation)
{
	if (sprite.GetAnimation() != &animation)
		sprite.SetAnimation(&animation);
}

Direction GetDirection(Key lastKey)
{
	if (lastKey == Key::A)
		return Direction::Left;

	if (lastKey == Key::D)
		return Direction::Right;

	if (lastKey == Key::W)
		return Direction::Up;

	if (lastKey == Key::S)
		return Direction::Down;

	return Direction::None;
}
