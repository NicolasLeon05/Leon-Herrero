#pragma once

#include "../sprite/Sprite.h"
#include "../EngineAPI.h"

class Tile : public Sprite
{
private:
	int id;
	int gid;

	int column;
	int row;
	int layerIndex;

	bool walkable;

public:
	ENGINE_API Tile();
	ENGINE_API ~Tile();

	ENGINE_API void SetId(int value);
	ENGINE_API int GetId();

	ENGINE_API void SetGid(int value);
	ENGINE_API int GetGid();

	ENGINE_API void SetGridPosition(int tileColumn, int tileRow, int tileLayerIndex);

	ENGINE_API int GetColumn();
	ENGINE_API int GetRow();
	ENGINE_API int GetLayerIndex();

	ENGINE_API void SetWalkable(bool value);
	ENGINE_API bool IsWalkable();
};