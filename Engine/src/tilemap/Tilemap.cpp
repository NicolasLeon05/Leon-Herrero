#include "Tilemap.h"

#include "tinyxml2.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <utility>

static const int FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
static const int FLIPPED_VERTICALLY_FLAG = 0x40000000;
static const int FLIPPED_DIAGONALLY_FLAG = 0x20000000;

static const int FLIP_FLAGS_MASK = FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG;

TileMap::TileMap() : Entity2D()
{
	width = 0;
	height = 0;

	tileWidth = 0;
	tileHeight = 0;

	firstGid = 1;

	tilesetTileCount = 0;
	tilesetColumns = 0;
	tilesetSpacing = 0;
	tilesetMargin = 0;

	imageWidth = 0;
	imageHeight = 0;

	loaded = false;
}

TileMap::~TileMap()
{
	Unload();
}

bool TileMap::Load(const std::string& filePath)
{
	Unload();

	mapPath = filePath;

	tinyxml2::XMLDocument mapDocument;
	tinyxml2::XMLError result = mapDocument.LoadFile(mapPath.c_str());

	if (result != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Failed to load tilemap: " << mapPath << std::endl;
		std::cout << mapDocument.ErrorStr() << std::endl;

		return false;
	}

	tinyxml2::XMLElement* mapElement = mapDocument.FirstChildElement("map");

	if (mapElement == nullptr)
	{
		std::cout << "The TMX file does not contain a map element" << std::endl;
		return false;
	}

	const char* orientation = mapElement->Attribute("orientation");

	if (orientation == nullptr || std::string(orientation) != "orthogonal")
	{
		std::cout << "Only orthogonal tilemaps are supported" << std::endl;
		return false;
	}

	width = mapElement->UnsignedAttribute("width");
	height = mapElement->UnsignedAttribute("height");
	tileWidth = mapElement->UnsignedAttribute("tilewidth");
	tileHeight = mapElement->UnsignedAttribute("tileheight");

	if (width == 0 || height == 0 || tileWidth == 0 || tileHeight == 0)
	{
		std::cout << "The tilemap has invalid dimensions" << std::endl;
		return false;
	}

	tinyxml2::XMLElement* tilesetReference = mapElement->FirstChildElement("tileset");

	if (tilesetReference == nullptr)
	{
		std::cout << "The tilemap does not contain a tileset" << std::endl;

		return false;
	}

	firstGid = tilesetReference->UnsignedAttribute("firstgid", 1);

	const char* tilesetSource = tilesetReference->Attribute("source");

	if (tilesetSource == nullptr)
	{
		std::cout << "Embedded tilesets are not supported" << std::endl;

		return false;
	}

	std::filesystem::path mapFilePath(mapPath);
	std::filesystem::path fullTilesetPath = mapFilePath.parent_path() / tilesetSource;
	tilesetPath = fullTilesetPath.lexically_normal().string();

	if (!LoadTileset(tilesetPath))
		return false;

	if (!textureImporter.LoadTexture(texturePath, true))
		return false;

	if (!LoadLayers(mapElement))
	{
		Unload();
		return false;
	}

	loaded = true;

	UpdateTileTransforms();

	std::cout << "Tilemap loaded successfully: " << width << " x " << height << " | Layers: " << layers.size() << std::endl;

	return true;
}

void TileMap::Unload()
{
	layers.clear();
	tileWalkability.clear();

	width = 0;
	height = 0;

	tileWidth = 0;
	tileHeight = 0;

	firstGid = 1;

	tilesetTileCount = 0;
	tilesetColumns = 0;
	tilesetSpacing = 0;
	tilesetMargin = 0;

	imageWidth = 0;
	imageHeight = 0;

	mapPath = "";
	tilesetPath = "";
	texturePath = "";
	transparentColor = "";

	loaded = false;
}

bool TileMap::LoadTileset(const std::string& path)
{
	tinyxml2::XMLDocument tilesetDocument;
	tinyxml2::XMLError result = tilesetDocument.LoadFile(path.c_str());

	if (result != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Failed to load tileset: " << path << std::endl;
		std::cout << tilesetDocument.ErrorStr() << std::endl;
		return false;
	}

	tinyxml2::XMLElement* tilesetElement = tilesetDocument.FirstChildElement("tileset");

	if (tilesetElement == nullptr)
	{
		std::cout << "The TSX file does not contain a tileset element" << std::endl;
		return false;
	}

	tilesetTileCount = tilesetElement->UnsignedAttribute("tilecount");
	tilesetColumns = tilesetElement->UnsignedAttribute("columns");
	tilesetSpacing = tilesetElement->UnsignedAttribute("spacing", 0);
	tilesetMargin = tilesetElement->UnsignedAttribute("margin", 0);

	if (tilesetTileCount == 0 || tilesetColumns == 0)
	{
		std::cout << "The tileset has invalid information" << std::endl;
		return false;
	}

	tinyxml2::XMLElement* imageElement = tilesetElement->FirstChildElement("image");

	if (imageElement == nullptr)
	{
		std::cout << "The tileset does not contain an image" << std::endl;

		return false;
	}

	const char* imageSource = imageElement->Attribute("source");

	if (imageSource == nullptr)
	{
		std::cout << "The tileset image does not contain a source" << std::endl;
		return false;
	}

	imageWidth = imageElement->UnsignedAttribute("width");
	imageHeight = imageElement->UnsignedAttribute("height");

	const char* transparentColorValue = imageElement->Attribute("trans");

	if (transparentColorValue != nullptr)
		transparentColor = transparentColorValue;
	else
		transparentColor = "";

	std::filesystem::path tilesetFilePath(path);
	std::filesystem::path fullTexturePath = tilesetFilePath.parent_path() / imageSource;
	texturePath = fullTexturePath.lexically_normal().string();

	tileWalkability.clear();

	for (tinyxml2::XMLElement* tileElement = tilesetElement->FirstChildElement("tile");
		tileElement != nullptr;
		tileElement = tileElement->NextSiblingElement("tile")
		)
	{
		int localId = tileElement->UnsignedAttribute("id");

		bool walkable = true;

		tinyxml2::XMLElement* propertiesElement = tileElement->FirstChildElement("properties");

		if (propertiesElement != nullptr)
		{
			for (tinyxml2::XMLElement* propertyElement = propertiesElement->FirstChildElement("property");
				propertyElement != nullptr;
				propertyElement = propertyElement->NextSiblingElement("property")
				)
			{
				const char* propertyName = propertyElement->Attribute("name");

				if (propertyName != nullptr && std::string(propertyName) == "walkable")
					walkable = propertyElement->BoolAttribute("value", true);
			}
		}

		tileWalkability[localId] = walkable;
	}

	return true;
}

bool TileMap::LoadLayers(tinyxml2::XMLElement* mapElement)
{
	layers.clear();

	int layerIndex = 0;

	for (
		tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
		layerElement != nullptr;
		layerElement = layerElement->NextSiblingElement("layer")
		)
	{
		TileLayer layer;

		const char* layerName = layerElement->Attribute("name");

		if (layerName != nullptr)
			layer.name = layerName;
		else
			layer.name = "";

		layer.width = layerElement->UnsignedAttribute("width", width);
		layer.height = layerElement->UnsignedAttribute("height", height);
		layer.index = layerIndex;
		layer.visible = layerElement->BoolAttribute("visible", true);

		tinyxml2::XMLElement* dataElement = layerElement->FirstChildElement("data");

		if (dataElement == nullptr)
		{
			std::cout << "Layer does not contain data: " << layer.name << std::endl;
			return false;
		}

		const char* encoding = dataElement->Attribute("encoding");

		if (encoding == nullptr || std::string(encoding) != "csv")
		{
			std::cout << "Only CSV layer encoding is supported" << std::endl;
			return false;
		}

		std::vector<int> gids;

		if (!ReadCsvData(dataElement->GetText(), gids))
			return false;

		int expectedTileCount = layer.width * layer.height;

		if (gids.size() != expectedTileCount)
		{
			std::cout << "Invalid number of tiles in layer: " << layer.name << std::endl;
			std::cout << "Expected: " << expectedTileCount << " | Found: " << gids.size() << std::endl;
			return false;
		}

		layer.tiles.resize(expectedTileCount);

		for (int row = 0; row < layer.height; row++)
		{
			for (int column = 0; column < layer.width; column++)
			{
				int tileIndex = row * layer.width + column;
				int rawGid = gids[tileIndex];

				if (rawGid == 0)
					continue;

				if (!CreateTile(layer, rawGid, column, row))
					return false;
			}
		}

		layers.push_back(std::move(layer));

		layerIndex++;
	}

	return !layers.empty();
}

bool TileMap::ReadCsvData(const char* csvText, std::vector<int>& gids)
{
	gids.clear();

	if (csvText == nullptr)
		return false;

	std::stringstream stream(csvText);
	std::string value;

	while (std::getline(stream, value, ','))
	{
		value.erase
		(
			std::remove_if(value.begin(), value.end(), [](char character)
				{
					return std::isspace(character) != 0;
				}),
			value.end()
		);

		if (value.empty())
		{
			continue;
		}

		try
		{
			long long parsedValue = std::stoull(value);
			gids.push_back(static_cast<int>(parsedValue));
		}
		catch (...)
		{
			std::cout << "Invalid GID in CSV: " << value << std::endl;
			return false;
		}
	}

	return true;
}

bool TileMap::CreateTile(TileLayer& layer, int rawGid, int column, int row)
{
	bool flippedHorizontally = (rawGid & FLIPPED_HORIZONTALLY_FLAG) != 0;
	bool flippedVertically = (rawGid & FLIPPED_VERTICALLY_FLAG) != 0;
	bool flippedDiagonally = (rawGid & FLIPPED_DIAGONALLY_FLAG) != 0;

	int gid = rawGid & ~FLIP_FLAGS_MASK;

	if (gid < firstGid)
		return false;

	int localId = gid - firstGid;

	if (localId >= tilesetTileCount)
	{
		std::cout << "Tile GID outside the tileset: " << gid << std::endl;
		return false;
	}

	std::unique_ptr<Tile> tile = std::make_unique<Tile>();

	tile->SetId(localId);
	tile->SetGid(gid);
	tile->SetGridPosition(column, row, layer.index);
	tile->SetWalkable(GetTileWalkable(localId));
	tile->SetSharedTexture(textureImporter.GetTexture());
	tile->CreateSquare(glm::vec3(0.0f), static_cast<float>(tileWidth), static_cast<float>(tileHeight));

	float topRightU = 0.0f;
	float topRightV = 0.0f;

	float bottomRightU = 0.0f;
	float bottomRightV = 0.0f;

	float bottomLeftU = 0.0f;
	float bottomLeftV = 0.0f;

	float topLeftU = 0.0f;
	float topLeftV = 0.0f;

	CalculateTextureCoordinates(
		localId,
		flippedHorizontally, flippedVertically, flippedDiagonally,
		topRightU, topRightV,
		bottomRightU, bottomRightV,
		bottomLeftU, bottomLeftV,
		topLeftU, topLeftV
	);

	tile->SetTextureCoordinates(
		topRightU, topRightV,
		bottomRightU, bottomRightV,
		bottomLeftU, bottomLeftV,
		topLeftU, topLeftV
	);

	int tileIndex = row * layer.width + column;
	layer.tiles[tileIndex] = std::move(tile);

	return true;
}

bool TileMap::GetTileWalkable(int localId)
{
	auto iterator = tileWalkability.find(localId);

	if (iterator == tileWalkability.end())
		return true;

	return iterator->second;
}

Tile* TileMap::GetTile(TileLayer& layer, int column, int row)
{
	if (column >= layer.width || row >= layer.height)
		return nullptr;

	int tileIndex = row * layer.width + column;
	return layer.tiles[tileIndex].get();
}

const Tile* TileMap::GetTile(const TileLayer& layer, int column, int row)
{
	if (column >= layer.width || row >= layer.height)
		return nullptr;

	int tileIndex = row * layer.width + column;
	return layer.tiles[tileIndex].get();
}

void TileMap::CalculateTextureCoordinates(
	int localId,
	bool flippedHorizontally, bool flippedVertically, bool flippedDiagonally,
	float& topRightU, float& topRightV,
	float& bottomRightU, float& bottomRightV,
	float& bottomLeftU, float& bottomLeftV,
	float& topLeftU, float& topLeftV
)
{
	int tilesetColumn = localId % tilesetColumns;
	int tilesetRow = localId / tilesetColumns;

	float pixelX = static_cast<float>(tilesetMargin + tilesetColumn * (tileWidth + tilesetSpacing));
	float pixelY = static_cast<float>(tilesetMargin + tilesetRow * (tileHeight + tilesetSpacing));

	float uMin = pixelX / static_cast<float>(imageWidth);
	float uMax = (pixelX + static_cast<float>(tileWidth)) / static_cast<float>(imageWidth);

	float vMax = 1.0f - pixelY / static_cast<float>(imageHeight);
	float vMin = 1.0f - (pixelY + static_cast<float>(tileHeight)) / static_cast<float>(imageHeight);

	CalculateFlippedUv(1.0f, 1.0f, uMin, uMax, vMin, vMax, flippedHorizontally, flippedVertically, flippedDiagonally, topRightU, topRightV);
	CalculateFlippedUv(1.0f, 0.0f, uMin, uMax, vMin, vMax, flippedHorizontally, flippedVertically, flippedDiagonally, bottomRightU, bottomRightV);
	CalculateFlippedUv(0.0f, 0.0f, uMin, uMax, vMin, vMax, flippedHorizontally, flippedVertically, flippedDiagonally, bottomLeftU, bottomLeftV);
	CalculateFlippedUv(0.0f, 1.0f, uMin, uMax, vMin, vMax, flippedHorizontally, flippedVertically, flippedDiagonally, topLeftU, topLeftV);
}

void TileMap::CalculateFlippedUv(
	float x, float y,
	float uMin, float uMax,
	float vMin, float vMax,
	bool flippedHorizontally, bool flippedVertically, bool flippedDiagonally,
	float& u, float& v)
{
	if (flippedDiagonally)
		std::swap(x, y);

	if (flippedHorizontally)
		x = 1.0f - x;

	if (flippedVertically)
		y = 1.0f - y;

	u = uMin + (uMax - uMin) * x;
	v = vMin + (vMax - vMin) * y;
}

void TileMap::UpdateTileTransforms()
{
	glm::mat4 mapTransform = GetTRS();
	glm::vec3 mapScale = GetScale();
	glm::vec3 mapRotation = GetRotation();

	for (TileLayer& layer : layers)
	{
		for (int row = 0; row < layer.height; row++)
		{
			for (int column = 0; column < layer.width; column++)
			{
				Tile* tile = GetTile(layer, column, row);

				if (tile == nullptr)
					continue;

				float localX = static_cast<float>(column * tileWidth) + static_cast<float>(tileWidth) * 0.5f;
				float localY = static_cast<float>((height - row - 1) * tileHeight) + static_cast<float>(tileHeight) * 0.5f;

				glm::vec4 worldPosition = mapTransform * glm::vec4(localX, localY, 0.0f, 1.0f);

				tile->SetPosition(worldPosition.x, worldPosition.y, worldPosition.z);
				tile->SetRotation(mapRotation.x, mapRotation.y, mapRotation.z);
				tile->SetScale(static_cast<float>(tileWidth) * mapScale.x, static_cast<float>(tileHeight) * mapScale.y, 1.0f);
			}
		}
	}
}

void TileMap::Update()
{
	if (!loaded)
	{
		return;
	}

	UpdateTileTransforms();

	for (TileLayer& layer : layers)
	{
		for (std::unique_ptr<Tile>& tile : layer.tiles)
		{
			if (tile != nullptr)
				tile->Update();
		}
	}
}

void TileMap::Draw()
{
	if (!loaded)
		return;

	for (TileLayer& layer : layers)
	{
		if (!layer.visible)
			continue;

		for (std::unique_ptr<Tile>& tile : layer.tiles)
		{
			if (tile != nullptr)
				tile->Draw();
		}
	}
}

int TileMap::GetWidth()
{
	return width;
}

int TileMap::GetHeight()
{
	return height;
}

int TileMap::GetTileWidth()
{
	return tileWidth;
}

int TileMap::GetTileHeight()
{
	return tileHeight;
}

bool TileMap::IsLoaded()
{
	return loaded;
}

bool TileMap::IsCellWalkable(int column, int row)
{
	if (column < 0 || row < 0 || column >= static_cast<int>(width) || row >= static_cast<int>(height))
		return false;

	bool walkable = false;

	for (TileLayer& layer : layers)
	{
		Tile* tile = GetTile(layer, column, row);

		if (tile != nullptr)
			walkable = tile->IsWalkable();
	}

	return walkable;
}

bool TileMap::CheckCollision(Entity2D& entity)
{
	if (!loaded)
		return false;

	float scaledTileWidth = static_cast<float>(tileWidth) * GetScale().x;
	float scaledTileHeight = static_cast<float>(tileHeight) * GetScale().y;
	float halfEntityWidth = collisionManager.GetCollisionWidthRotated(&entity) * 0.5f;
	float halfEntityHeight = collisionManager.GetCollisionHeightRotated(&entity) * 0.5f;

	float localLeft = entity.GetX() - halfEntityWidth - GetX();
	float localRight = entity.GetX() + halfEntityWidth - GetX();
	float localBottom = entity.GetY() - halfEntityHeight - GetY();
	float localTop = entity.GetY() + halfEntityHeight - GetY();

	const float margin = 0.001f;

	int leftColumn = (std::floor(localLeft / scaledTileWidth));
	int rightColumn = (std::floor((localRight - margin) / scaledTileWidth));
	int bottomRow = (std::floor(localBottom / scaledTileHeight));
	int topRow = (std::floor((localTop - margin) / scaledTileHeight));

	for (int rowFromBottom = bottomRow; rowFromBottom <= topRow; rowFromBottom++)
	{
		int tiledRow = (height) - rowFromBottom - 1;

		for (int column = leftColumn; column <= rightColumn; column++)
		{
			if (!IsCellWalkable(column, tiledRow))
			{
				entity.SetPosition(entity.GetPrevPosition());
				return true;
			}
		}
	}

	return false;
}
