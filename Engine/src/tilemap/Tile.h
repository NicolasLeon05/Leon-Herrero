#pragma once

#include "../sprite/Sprite.h"
#include "../EngineAPI.h"

class Tile : public Sprite
{
private:
	unsigned int id;
	unsigned int gid;

	unsigned int column;
	unsigned int row;
	unsigned int layerIndex;

	bool walkable;

public:
	ENGINE_API Tile();
	ENGINE_API ~Tile();

	ENGINE_API void SetId(unsigned int value);
	ENGINE_API unsigned int GetId() const;

	ENGINE_API void SetGid(unsigned int value);
	ENGINE_API unsigned int GetGid() const;

	ENGINE_API void SetGridPosition(unsigned int tileColumn, unsigned int tileRow, unsigned int tileLayerIndex);

	ENGINE_API unsigned int GetColumn() const;
	ENGINE_API unsigned int GetRow() const;
	ENGINE_API unsigned int GetLayerIndex() const;

	ENGINE_API void SetWalkable(bool value);
	ENGINE_API bool IsWalkable() const;
};