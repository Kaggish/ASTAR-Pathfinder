#pragma once
#include "raylib.h"
#include <vector>
#include <functional>

class Tile
{
private:
	Vector2 position;
	int textureID;
	int uniqueID;

	Rectangle collisionBox_entity;

	bool isBlocked = false;
	bool isOccupied = false;

	Texture2D dirtTexture;
	Texture2D wallTexture;

public:
	std::vector<int> neighborIndex;
	Tile() = default;
	Tile(Vector2 position);
	~Tile() = default;

	void collisionBox();
	void draw();

	Vector2 getPosition() const;
	int getTextureID();
	int getUniqueID() const;
	bool getBlocked() const;
	bool getOccupied() const;
	Rectangle getCollisionBox() const;

	void setDirtTextures(Texture2D _dirt);
	void setWallTextures(Texture2D _wall);
	void setTextureID(int _id);
	void setUniqueID(int _id);
	void setBlocked(bool blocked);
	void setOccupied(bool occupied);
	void setPosition(float posX, float posY);
};

class Grid
{
	static Grid* instance;
	const float width;
	const float height;
	float tileDiameter;
	float gridsizeX;
	float gridsizeY;

	Texture2D dirtTexture;
	Texture2D wallTexture;

	int frameTime = 0;

private:
	void loadTextures();
	void createMap();
	void positionTiles();


public:
	static Grid& getInstance();
	std::vector<Tile*> tile;
	Grid();
	const Tile* getTileIf(const std::function<bool(const Tile*)>& Query) const;
	~Grid();
	void onStart();
	void update();
	void draw();

	void unloadTextures();
};