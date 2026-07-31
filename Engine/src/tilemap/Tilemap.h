#pragma once

#include "../entity/Entity2D.h"
#include "../CollisionManager/CollisionManager.h"
#include "../textureImporter/TextureImporter.h"
#include "../EngineAPI.h"

#include "Tile.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace tinyxml2
{
	class XMLElement;
}

class TileMap : public Entity2D
{
private:
	struct TileLayer
	{
		std::string name;

		unsigned int width;
		unsigned int height;
		unsigned int index;

		bool visible;

		std::vector<std::unique_ptr<Tile>> tiles;
	};

	unsigned int width;
	unsigned int height;

	unsigned int tileWidth;
	unsigned int tileHeight;

	unsigned int firstGid;

	unsigned int tilesetTileCount;
	unsigned int tilesetColumns;
	unsigned int tilesetSpacing;
	unsigned int tilesetMargin;

	unsigned int imageWidth;
	unsigned int imageHeight;

	std::string mapPath;
	std::string tilesetPath;
	std::string texturePath;
	std::string transparentColor;

	std::unordered_map<unsigned int, bool> tileWalkability;

	std::vector<TileLayer> layers;

	TextureImporter textureImporter;
	CollisionManager collisionManager;

	bool loaded;

	bool LoadTileset(const std::string& path);
	bool LoadLayers(tinyxml2::XMLElement* mapElement);

	bool ReadCsvData(const char* csvText, std::vector<unsigned int>& gids);

	bool CreateTile(TileLayer& layer, unsigned int rawGid, unsigned int column, unsigned int row);

	bool GetTileWalkable(unsigned int localId) const;

	Tile* GetTile(TileLayer& layer, unsigned int column, unsigned int row);
	const Tile* GetTile(const TileLayer& layer, unsigned int column, unsigned int row) const;

	void CalculateTextureCoordinates(
		unsigned int localId,
		bool flippedHorizontally, bool flippedVertically, bool flippedDiagonally,
		float& topRightU, float& topRightV,
		float& bottomRightU, float& bottomRightV,
		float& bottomLeftU, float& bottomLeftV,
		float& topLeftU, float& topLeftV
	) const;

	void CalculateFlippedUv(float x, float y,
		float uMin, float uMax,
		float vMin, float vMax,
		bool flippedHorizontally, bool flippedVertically, bool flippedDiagonally,
		float& u, float& v
	) const;

	void UpdateTileTransforms();

public:
	ENGINE_API TileMap();
	ENGINE_API ~TileMap();

	TileMap(const TileMap&) = delete;
	TileMap& operator=(const TileMap&) = delete;

	ENGINE_API bool Load(const std::string& filePath);
	ENGINE_API void Unload();

	ENGINE_API void Update() override;
	ENGINE_API void Draw() override;

	ENGINE_API unsigned int GetWidth() const;
	ENGINE_API unsigned int GetHeight() const;

	ENGINE_API unsigned int GetTileWidth() const;
	ENGINE_API unsigned int GetTileHeight() const;

	ENGINE_API bool IsLoaded() const;

	//ENGINE_API bool IsCellWalkable(int column, int row) const;

	//ENGINE_API bool CheckCollision(Entity2D& entity);
};