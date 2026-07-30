#include "Tile.h"

Tile::Tile()
{
	id = 0;
	gid = 0;

	column = 0;
	row = 0;
	layerIndex = 0;

	walkable = true;
}

Tile::~Tile()
{

}

void Tile::SetId(unsigned int value)
{
	id = value;
}

unsigned int Tile::GetId() const
{
	return id;
}

void Tile::SetGid(unsigned int value)
{
	gid = value;
}

unsigned int Tile::GetGid() const
{
	return gid;
}

void Tile::SetGridPosition(unsigned int tileColumn, unsigned int tileRow, unsigned int tileLayerIndex)
{
	column = tileColumn;
	row = tileRow;
	layerIndex = tileLayerIndex;
}

unsigned int Tile::GetColumn() const
{
	return column;
}

unsigned int Tile::GetRow() const
{
	return row;
}

unsigned int Tile::GetLayerIndex() const
{
	return layerIndex;
}

void Tile::SetWalkable(bool value)
{
	walkable = value;
}

bool Tile::IsWalkable() const
{
	return walkable;
}