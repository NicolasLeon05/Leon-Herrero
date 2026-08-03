#pragma once

#include "sprite/Sprite.h"
#include "shape/Shape.h"
#include "animation/Animation.h"
#include "tilemap/Tilemap.h"
#include "BaseGame.h"

class Game : public BaseGame
{
private:
	TileMap tileMap;
	Sprite player;
	Animation animation;
	Shape shape;

	float scaledTileWidth;
	float scaledTileHeight;
	float speedLimitCounter;

	static const float screenWidth;
	static const float screenHeight;

	float playerWidth;
	float playerHeight;
	float timeToMove;

	void InitializeTileMap();
	void InitializePlayer();
	void UpdatePlayerMovement(float deltaTime);

public:
	Game();

	void InitGame() override;
	void Update() override;
	void DeInitGame() override;
};