#pragma once

#include "sprite/Sprite.h"
#include "animation/Animation.h"
#include "tilemap/Tilemap.h"
#include "BaseGame.h"
#include "Direction.h"

class Game : public BaseGame
{
private:
	TileMap tileMap;
	Sprite player;

	Animation playerUp;
	Animation playerDown;
	Animation playerLeft;
	Animation playerRight;

	Sprite bulletSprite;
	Animation bulletUp;
	Animation bulletDown;
	Animation bulletRight;
	Animation bulletLeft;
	Animation explosion;

	bool bulletFired;

	float scaledTileWidth;
	float scaledTileHeight;

	static const float screenWidth;
	static const float screenHeight;

	void InitializeTileMap();
	void InitializeEntities();
	void UpdatePlayerMovement(float deltaTime);
	void SetBulletFirstMovement();
	void UpdateBulletMovement(float deltaTime, float speed);

public:
	Game();

	void InitGame() override;
	void Update() override;
	void DeInitGame() override;
};