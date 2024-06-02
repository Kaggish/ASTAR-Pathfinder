#include "Grid.h"

Grid* Grid::instance = nullptr;

void Tile::setPosition(float posX, float posY)
{
	position.x = posX;
	position.y = posY;
}

Tile::Tile(Vector2 position)
	: position(position)
	, textureID(0)
	, uniqueID(0)
{
}

void Tile::collisionBox()
{
	collisionBox_entity.x = position.x;
	collisionBox_entity.y = position.y;
	collisionBox_entity.width = static_cast <float> (dirtTexture.width);
	collisionBox_entity.height = static_cast <float> (dirtTexture.height);
}

void Tile::draw()
{
	if (textureID == 2)
	{
		DrawTextureRec(dirtTexture, Rectangle{ 0, 0, static_cast <float> (dirtTexture.width),static_cast <float> (dirtTexture.height) }, position, WHITE);
	}
	else
	{
		DrawTextureRec(wallTexture, Rectangle{ 0, 0, static_cast <float> (wallTexture.width),static_cast <float> (wallTexture.height) }, position, WHITE);
	}
}

Vector2 Tile::getPosition() const
{
    return position;
}

int Tile::getTextureID()
{
    return textureID;
}

int Tile::getUniqueID() const
{
	return uniqueID;
}

bool Tile::getBlocked() const
{
	return isBlocked;
}

bool Tile::getOccupied() const
{
	return isOccupied;
}

Rectangle Tile::getCollisionBox() const
{
	return collisionBox_entity;
}

void Tile::setDirtTextures(Texture2D _dirt)
{
	dirtTexture = _dirt;
}

void Tile::setWallTextures(Texture2D _wall)
{
	wallTexture = _wall;
}

void Tile::setTextureID(int _id)
{
	textureID = _id;
}

void Tile::setUniqueID(int _id)
{
	uniqueID = _id;
}

void Tile::setBlocked(bool blocked)
{
	isBlocked = blocked;
}

void Tile::setOccupied(bool occupied)
{
	isOccupied = occupied;
}

void Grid::loadTextures()
{
	dirtTexture = LoadTexture("Assets/Dirt.png");

	wallTexture = LoadTexture("Assets/Wall.png");
}

void Grid::createMap()
{
	for (int Y = 0; Y < gridsizeY; ++Y)
	{
		for (int X = 0; X < gridsizeX; ++X)
		{
			tile.push_back(new Tile(Vector2(X * tileDiameter, Y * tileDiameter)));
		}
	}

	// Cache all neigbors
	for (int Y = 0; Y < gridsizeY; ++Y)
	{
		for (int X = 0; X < gridsizeX; ++X)
		{
			const int Index = Y * gridsizeX + X;
			Tile& neigbor = *tile[Index];

			neigbor.neighborIndex.reserve(8);
			if (X > 0)
			{
				neigbor.neighborIndex.push_back(Index - 1);
			}
			if (X < gridsizeX - 1)
			{
				neigbor.neighborIndex.push_back(Index + 1);
			}
			if (Y > 0)
			{
				neigbor.neighborIndex.push_back(Index - gridsizeX);
			}
			if (Y < gridsizeY - 1)
			{
				neigbor.neighborIndex.push_back(Index + gridsizeX);
			}

			if (X > 0 && Y > 0)
			{
				neigbor.neighborIndex.push_back((Index - gridsizeX) - 1);
			}
			if (X < gridsizeX - 1 && Y > 0)
			{
				neigbor.neighborIndex.push_back((Index - gridsizeX) + 1);
			}
			if (X > 0 && Y < gridsizeY - 1)
			{
				neigbor.neighborIndex.push_back((Index + gridsizeX) - 1);
			}
			if (X < gridsizeX - 1 && Y < gridsizeY - 1)
			{
				neigbor.neighborIndex.push_back((Index + gridsizeX) + 1);
			}
			
		}
	}
}

void Grid::positionTiles()
{
	float tileRadius = 25;
	tileDiameter = tileRadius * 2;
	gridsizeX = (width / tileDiameter);
	gridsizeY = (height / tileDiameter);
	loadTextures();
	createMap();

	for (int i = 0; i < tile.size(); ++i)
	{
		int v1 = GetRandomValue(1, 2);
		tile.at(i)->setTextureID(v1);
		tile.at(i)->setUniqueID(i);
		if (tile.at(i)->getTextureID() == 2)
		{
			tile.at(i)->setBlocked(false);
		}
		else
		{
			tile.at(i)->setBlocked(true);
		}
	}

	for (int i = 0; i < tile.size(); ++i)
	{
		tile.at(i)->setDirtTextures(dirtTexture);
		tile.at(i)->setWallTextures(wallTexture);
	}
}

Grid& Grid::getInstance()
{
	static Grid grid;
	return grid;
}

Grid::Grid()
	:width(1250)
	, height(750)
	, gridsizeX(0)
	, gridsizeY(0)
	, tileDiameter(0)
{
}

void Grid::onStart()
{
	positionTiles();
}

void Grid::update()
{
	for(int i = 0; i < tile.size(); ++i)
	{
		tile.at(i)->collisionBox();
		if (tile.at(i)->getTextureID() == 2)
		{
			tile.at(i)->setBlocked(false);
		}
		else
		{
			tile.at(i)->setBlocked(true);
		}
	}
}

void Grid::draw()
{
	for (int i = 0; i < tile.size(); ++i)
	{
		tile.at(i)->draw();
	}
}

void Grid::unloadTextures()
{
}

const Tile* Grid::getTileIf(const std::function<bool(const Tile*)>& Query) const
{
	const auto FoundIterator = std::find_if(tile.begin(), tile.end(), Query);
	return (FoundIterator == tile.end()) ? nullptr : *FoundIterator._Ptr;
}

Grid::~Grid()
{
	Grid::instance = nullptr;
}
