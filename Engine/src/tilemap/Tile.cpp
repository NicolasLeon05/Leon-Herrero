#include "Tile.h"

Tile::Tile()
{
	id = 0;
	gid = 0;

	column = 0;
	row = 0;
	layerIndex = 0;

	walkable = false;
}

Tile::~Tile()
{

}

void Tile::SetId(int value)
{
	id = value;
}

int Tile::GetId()
{
	return id;
}

void Tile::SetGid(int value)
{
	gid = value;
}

int Tile::GetGid()
{
	return gid;
}

void Tile::SetGridPosition(int tileColumn, int tileRow, int tileLayerIndex)
{
	column = tileColumn;
	row = tileRow;
	layerIndex = tileLayerIndex;
}

int Tile::GetColumn()
{
	return column;
}

int Tile::GetRow()
{
	return row;
}

int Tile::GetLayerIndex()
{
	return layerIndex;
}

void Tile::SetWalkable(bool value)
{
	walkable = value;
}

bool Tile::IsWalkable()
{
	return walkable;
}