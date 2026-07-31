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

		int width;
		int height;
		int index;

		bool visible;

		std::vector<std::unique_ptr<Tile>> tiles;
	};

	int width;
	int height;

	int tileWidth;
	int tileHeight;

	int firstGid;

	int tilesetTileCount;
	int tilesetColumns;
	int tilesetSpacing;
	int tilesetMargin;

	int imageWidth;
	int imageHeight;

	std::string mapPath;
	std::string tilesetPath;
	std::string texturePath;
	std::string transparentColor;

	std::unordered_map<int, bool> tileWalkability;

	std::vector<TileLayer> layers;

	TextureImporter textureImporter;
	CollisionManager collisionManager;

	bool loaded;

	bool LoadTileset(const std::string& path);
	bool LoadLayers(tinyxml2::XMLElement* mapElement);

	bool ReadCsvData(const char* csvText, std::vector<int>& gids);

	bool CreateTile(TileLayer& layer, int rawGid, int column, int row);

	bool GetTileWalkable(int localId);

	Tile* GetTile(TileLayer& layer, int column, int row);
	const Tile* GetTile(const TileLayer& layer, int column, int row);

	void CalculateTextureCoordinates(
		int localId,
		bool flippedHorizontally, bool flippedVertically, bool flippedDiagonally,
		float& topRightU, float& topRightV,
		float& bottomRightU, float& bottomRightV,
		float& bottomLeftU, float& bottomLeftV,
		float& topLeftU, float& topLeftV
	);

	void CalculateFlippedUv(float x, float y,
		float uMin, float uMax,
		float vMin, float vMax,
		bool flippedHorizontally, bool flippedVertically, bool flippedDiagonally,
		float& u, float& v
	);

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

	ENGINE_API int GetWidth();
	ENGINE_API int GetHeight();

	ENGINE_API int GetTileWidth();
	ENGINE_API int GetTileHeight();

	ENGINE_API bool IsLoaded();

	ENGINE_API bool IsCellWalkable(int column, int row);

	ENGINE_API bool CheckCollision(Entity2D& entity);
};