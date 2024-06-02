#pragma once
#include "raylib.h"
#include <unordered_map>
#include "Grid.h"
#include "Entity.h"

class Star : public Entity
{
private:
	Vector2 position;

	Texture2D starTexture;
private:
	void setEntityPositionOnStart(std::unordered_map<int, Tile> validPosition) override;
	void setEntityPosition(std::unordered_map<int, Tile> validPosition, int i) override;

public:


	void loadTextures();
	void onStart(std::unordered_map<int, Tile> validPosition) override; // set texture, position
	void update(std::unordered_map<int, Tile> validPosition, int i) override;
	void draw() override;

	Vector2 getPosition();

	void setPosition(Vector2 _position);
};